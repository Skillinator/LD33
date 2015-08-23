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
#include "messages.h"

ChangeBarGraphMessage::ChangeBarGraphMessage(){
	messageType = MESSAGE_BARGRAPH_CHANGE;
	change = 0;
	target = "nul";
}

ChangeBarGraphMessage::ChangeBarGraphMessage(std::string tar, float delta){
	messageType = MESSAGE_BARGRAPH_CHANGE;
	target = tar;
	change = delta;
}

SetBarGraphMessage::SetBarGraphMessage(){
	messageType = MESSAGE_BARGRAPH_SET;
	target = "nul";
	value = 0;
}

SetBarGraphMessage::SetBarGraphMessage(std::string tar, float val){
	messageType = MESSAGE_BARGRAPH_SET;
	target = tar;
	value = val;
}