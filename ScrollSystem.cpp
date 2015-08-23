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

extern Engine* theEngine;
extern int windowheight;
extern int windowwidth;

ScrollSystem::ScrollSystem(int mw, int mh){
	id = SYSTEM_SCROLL;
	handler = new ScrollSystemHandler();

	mapWidth = mw;
	mapHeight = mh;

}

void ScrollSystem::update(float delta){
  // We do nothing!
}
	 
