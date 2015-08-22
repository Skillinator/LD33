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

TimedMessageSystem::TimedMessageSystem(){
  std::cout<<"sup";
	id = SYSTEM_TIMEDMESSAGE;
}

void TimedMessageSystem::update(float delta){
  for(int iterator = 0; iterator < numEntities(); iterator++){
    Entity *ent = entityAt(iterator);

    if(ent->hasComponent(COMPONENT_TIMEDMESSAGE)){
      TimedMessage *tm = static_cast<TimedMessage*>(ent->getComponent(COMPONENT_TIMEDMESSAGE));

      tm->progress(delta);

      if(tm->getTime() <= 0){
        if(tm->getTarget() == "loadMainMenu"){
          messageSystems(new LoadSceneMessage("main"));
        }
      }
    }
  }
}
	 
