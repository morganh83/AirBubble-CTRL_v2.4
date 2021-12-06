#ifndef CONFIG_H
#define CONFIG_H

struct configData
{
	char projectName[32];
	char mqttURL[64];
	uint16_t mqttPort;
	char mqttUserName[32];
	char mqttPass[64];
	char mSub[128];
	char mPub[128];
	char devName[32];
	char language[3];
};

extern uint32_t configVersion;
extern const configData defaults;

#endif