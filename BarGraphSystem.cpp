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
#include "ld33.h"

extern Engine* theEngine;

BarGraphSystem::BarGraphSystem(){
	id = SYSTEM_BARGRAPH;
  handler = new BarGraphSystemHandler();
}

void BarGraphSystem::update(float delta){

  // Do Nothing

}
	 
