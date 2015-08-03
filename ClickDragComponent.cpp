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

ClickDrag::ClickDrag(){
	xOffset = 0;
	yOffset = 0;
	active = false;
	id = COMPONENT_CLICKDRAG;
}

Component* ClickDrag::spawn(std::string sig, std::string args){
	return new ClickDrag();
}

float ClickDrag::getXOffset(){ return xOffset; }
float ClickDrag::getYOffset(){ return yOffset; }
bool ClickDrag::getActive(){ return active; }

void ClickDrag::initiate(float x, float y){
	active = true;
	xOffset = x;
	yOffset = y;
}

void ClickDrag::release(){
	active = false;
}

