#include <iostream>
#include <ctime>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "SOIL.h"
#include "skilLib.h"
#include "systems.h"
#include "components.h"
#include "messages.h"

extern Engine *theEngine;

System::System(){
	handler = new MessageHandler();
}

void System::engineMessage(Message *m){
	theEngine->recieveMessage(m);
}

Entity *System::entityAt(int index){
	return theEngine->getEntity(index);
}

int System::numEntities(){
	return theEngine->numEntities();
}

void System::recieveMessage(Message *m){ /* default shouldn't need to do much I think */ }

void System::setIndex(int ind){
	index = ind;
}

int System::getID(){
	return id;
}

void System::message(Message* msg){
	handler->handle(msg, this);
}