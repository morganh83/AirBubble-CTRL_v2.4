#include <Arduino.h>
#include "LittleFS.h"
#include <SPI.h>
#include "WiFiManager.h"
#include "webServer.h"
#include "updater.h"
#include "fetch.h"
#include "configManager.h"
#include "timeSync.h"
#include <MQTT.h>

WiFiClient espClient;
MQTTClient client;

const char* mSub = "mqtt/publish/cmd"; 
const char* mPub = "mqtt/subscribe/response";
const char* mqttURL = "mqtt.maker2maker.com";
const char* userName = "your_username";
const char* mqttPass = "your_password";
const char* devName = "unique_name";
const uint16_t mqttPort = 1883;


//Switch & Button States
int switchState;
int lastSwitchState = LOW;
int buttonState;
int lastButtonState = LOW;
int previous = LOW;

// Pins
const int switch1 = D7; //Switch pin
const int button1 = D0; //Button pin
int redPin = D3;
int greenPin = D2;
int bluePin = D1;

// Time settings
long btime = 0;
unsigned long debounceDelay = 400; // Change if flickering

void setLEDColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
void LEDOff() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}
void yellowColor() {
  setLEDColor(244, 50, 0);
}
void redColor() {
  setLEDColor(255, 0, 0);
}

void messageReceived(String &topic, String &payload) {
  Serial.println("Received: " + topic + " - " + payload);
  if (payload == "onCallAck") {
    //Serial.print("Received: Red");
    redColor();
  }
  else if (payload == "busyAck") {
    //Serial.print("Received: Yellow\n");
    yellowColor();
  }
  else if (payload == "clearAck") {
    //Serial.print("Received: Clear\n");
    LEDOff();
  }
}
//void forget();
void saveCallback() {
    Serial.println("EEPROM saved"); 
    //forget;
}

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  //Serial.print("\nconnecting...");
  Serial.print("Connected!\n");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  Serial.print("MQTT connecting...");
  Serial.print(mqttURL);
  Serial.print("\n");
  Serial.print("Username: ");
  Serial.print(userName);
  Serial.print("\n");
  Serial.print("Password: ");
  Serial.print(mqttPass);
  Serial.print("\n");
  Serial.print("Subscribing to: ");
  Serial.print(mSub);
  Serial.print("\n");
  Serial.print("Publishing to: ");
  Serial.print(mPub);
  Serial.print("\n");
  while (!client.connect(devName, userName, mqttPass)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
  client.subscribe(mSub);
}

void setup()
{
    Serial.begin(115200);
    LittleFS.begin();
    GUI.begin();
    configManager.begin();
    configManager.setConfigSaveCallback(saveCallback);
    WiFiManager.begin(configManager.data.projectName);
    timeSync.begin();
    client.begin(mqttURL, mqttPort, espClient);
    client.onMessage(messageReceived);
    //client.subscribe(mSub);
    //Setup the button and switch pins
    pinMode(button1, INPUT);
    pinMode(switch1, INPUT_PULLUP);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    LEDOff();
    //connect();
};

void loop()
{
    WiFiManager.loop();
    updater.loop();
    configManager.loop();
    client.loop();

    if (!WiFiManager.isCaptivePortal()) {
      if (!client.connected()) {
        connect();
      }
      //return;
    }
    // Set current switch and button state on boot
    switchState = digitalRead(switch1);
    int reading = digitalRead(button1);

    // Read and interact with the switch and button to send appropriate messages
    if (switchState != lastSwitchState) {
        if (switchState == HIGH) {
            Serial.print("Switch is ON\n");
            client.publish(mPub, "busy");
            Serial.print("busy Signal Sent\n");
        }
        else {
            Serial.print("Switch is OFF\n");
            client.publish(mPub, "clear");
            delay(200);
            Serial.print("clear Signal Sent\n");
        }
        lastSwitchState = switchState;
    }
    if (reading == HIGH && previous == LOW && millis() - btime > debounceDelay) {
        if (buttonState == HIGH) {
            buttonState = LOW;
            Serial.print("Button toggled: OFF\n");
            client.publish(mPub, "clear");
            Serial.print("clear Signal Sent\n");
        }
        else {
            buttonState = HIGH;
            Serial.print("Button toggled: ON\n");
            client.publish(mPub, "onCall");
            Serial.print("onCall Signal Sent\n");
        }  
        btime = millis();
    }
    previous = reading;
}
