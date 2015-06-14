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

Component::Component(){
id = COMPONENT_NONE;
}
Component::~Component(){

}
int Component::getID(){
	return id;
}

void Component::setID(int getid){
	id = getid;
}
