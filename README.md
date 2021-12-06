This repository is a specific build of the "On-Air" project (https://www.thingiverse.com/thing:3111075)
It adds a wifi fallback captive portal so that you can configure your wifi credentials. This is still a work in progress.

How to use:
This project was build in VS Code using PlatformIO. First, download VS Code from Microsoft and add the PlatformIO extension.
Other extensions you will need:
 - NPM

To initialize the environment, add the git repo(s) to your workspace

![image](https://user-images.githubusercontent.com/8813326/144888291-9df3a6e1-50d3-49c3-8db2-045cd039f684.png)

Then go into each .pio/libdeps/ESP8266 IoT Framework/
Right-click on "gui" and select "Open in Integrated Terminal"

![image](https://user-images.githubusercontent.com/8813326/144888582-a8834898-7b6e-49b0-abe0-2f2b0cade819.png)

Type "npm ci" to initialize NPM for building the web component.

Now you should be able to make any changes necessary to the code and rebuild it.
NOTE:
If you plan on making changes to the web (captive portal) you will want to uncomment the "build_flags" line and the DREBUILD lines in the platformio.ini file.


Known Bugs:
 - When connecting to the SSID, you do not get a DHCP IP
 - MQTT Configs do not work. Must hard-code them

TODO:
 - Fix configuration section to allow changing MQTT details
 - Create new dashboard to control light and display current status
 - Fix DHCP server
 - Make pretty
