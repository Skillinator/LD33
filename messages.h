#ifndef _skilLibMessaging
#define _skilLibMessaging

#include <stdio.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <string>
#include "skilLib.h"
#include "systems.h"

const int MESSAGE_UNDEFINED = -1;
const int MESSAGE_DELTA = 1;
const int MESSAGE_CONSOLEOUT = 2;

class DeltaMessage : public Message{
public:
	DeltaMessage();
	DeltaMessage(float d);
	float delta;
};


class ConsoleOutMessage : public Message{
public:
	ConsoleOutMessage();
	ConsoleOutMessage(std::string msg);
	std::string message;
};

#endif
