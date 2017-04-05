#ifndef INPUT_EVENT_SYSTEM_H
#define INPUT_EVENT_SYSTEM_H

class seEngine;

enum seEventType
{
	EventType_Size = 0,
	EventType_Count,
};

struct seInputPackage
{
	seEventType msg;
	float param[2];
};

class seInputEventSystem
{
public:
	seInputEventSystem(seEngine* engine);
	virtual bool OnMsg(seInputPackage& iEvent);
protected:
	seEngine* mEngine;
};

#endif
