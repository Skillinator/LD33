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

ScrollMessage::ScrollMessage(){
	messageType = MESSAGE_SCROLL;
	changex = changey = 0;
}

ScrollMessage::ScrollMessage(float cx, float cy){
	messageType = MESSAGE_SCROLL;
	changex = cx;
	changey = cy;
}