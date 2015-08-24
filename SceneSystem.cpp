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

SceneSystem::SceneSystem(){
	id = SYSTEM_LOADSCENE;
  handler = new SceneSystemHandler();
  names.push_back("main");
  paths.push_back("res/mainMenu.xupl");

  names.push_back("win");
  paths.push_back("res/win.xupl");

  names.push_back("lose");
  paths.push_back("res/lose.xupl");
}

void SceneSystem::update(float delta){
  // We do nothing!
}
	 
