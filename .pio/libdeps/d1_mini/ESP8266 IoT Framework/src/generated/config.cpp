#include <Arduino.h>
#include "config.h"

uint32_t configVersion = 840919266; //generated identifier to compare config with EEPROM

const configData defaults PROGMEM =
{
	"AirBubble CTRL",
	"mqtt.example.com",
	1883,
	"Username",
	"*********",
	"airbubble/sub",
	"airbubble/pub",
	"unique_name",
	"en"
};