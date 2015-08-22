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

extern Engine *theEngine;

SceneSystemHandler::SceneSystemHandler(){
	// Nothing doing
}


void SceneSystemHandler::handle(Message *m, Entity *ent){
	
	// Nothing doing here lol
}

void SceneSystemHandler::handle(Message *m, System *sys){
	SceneSystem *ss = static_cast<SceneSystem*>(sys);
	LoadSceneMessage *lsm = static_cast<LoadSceneMessage*>(m);
	if(m->messageType == MESSAGE_CHANGESCENE){
		for(int i = 0; i < ss->names.size(); i++){
			if(ss->names.size() == 0)
				return;

			if(ss->names[i] == lsm->scene)
				theEngine->loadXUPL(ss->paths[i]);

		}
	}
}