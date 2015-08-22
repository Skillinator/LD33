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
#include <math.h>

LoadSceneMessage::LoadSceneMessage(){
	scene = "";
	messageType = MESSAGE_CHANGESCENE;
}

LoadSceneMessage::LoadSceneMessage(std::string s){
	messageType = MESSAGE_CHANGESCENE;
	scene = s;
}