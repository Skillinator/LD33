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

StringMessageOnClick::StringMessageOnClick(){
	message = "null";
	id = COMPONENT_STRINGMESSAGEONCLICK;
}

StringMessageOnClick::StringMessageOnClick(std::string msg){
	message = msg;
	id = COMPONENT_STRINGMESSAGEONCLICK;
}

Component* StringMessageOnClick::spawn(std::string sig, std::string args){
	std::vector<std::string> arguments = split(args, ' ');
	arguments.erase(arguments.begin());
	if(sig.compare("s") == 0){
	    return new StringMessageOnClick(arguments[0]);
  }
	return new StringMessageOnClick();
}