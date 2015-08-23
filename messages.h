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
const int MESSAGE_CHANGESCENE = 3;
const int MESSAGE_SCROLL = 4;
const int MESSAGE_BARGRAPH_CHANGE = 5;
const int MESSAGE_BARGRAPH_SET = 6;

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

class LoadMainMenuMessage : public Message{
public:
	LoadMainMenuMessage();
};

class LoadSceneMessage : public Message{
public:
	LoadSceneMessage();
	LoadSceneMessage(std::string s);
	std::string scene;
};

class SceneSystemHandler : public MessageHandler{
public:
	SceneSystemHandler();
	void handle(Message*, Entity*);
	void handle(Message*, System*);
};

class ScrollSystemHandler : public MessageHandler{
public:
	ScrollSystemHandler();
	void handle(Message*, Entity*);
	void handle(Message*, System*);
};

class BarGraphSystemHandler : public MessageHandler{
public:
	BarGraphSystemHandler();
	void handle(Message*, Entity*);
	void handle(Message*, System*);
};

class ChangeBarGraphMessage : public Message{
public:
	ChangeBarGraphMessage();
	ChangeBarGraphMessage(std::string tar, float delta);
	std::string target;
	float change;
};

class SetBarGraphMessage : public Message{
public:
	SetBarGraphMessage();
	SetBarGraphMessage(std::string tar, float val);
	std::string target;
	float value;
};

class ScrollMessage : public Message{
public:
	ScrollMessage();
	ScrollMessage(float cx, float cy);
	float changex;
	float changey;
};

#endif
