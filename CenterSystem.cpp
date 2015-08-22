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

CenterSystem::CenterSystem(){
	id = SYSTEM_CENTER;
}
CenterSystem::CenterSystem(int w, int h){
  id = SYSTEM_CENTER;
  width = w;
  height = h;
}

void CenterSystem::update(float delta){
  for(int iterator = 0; iterator < numEntities(); iterator++){
    Entity *ent = entityAt(iterator);

    if(ent->hasComponent(COMPONENT_POSITION) && ent->hasComponent(COMPONENT_CENTER)){
      Center *c = static_cast<Center*>(ent->getComponent(COMPONENT_CENTER));
      Position *pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));

      if(c->getHorizontal())
        pos->setX(width/2);

      if(c->getVertical())
        pos->setY(height/2);
    }

  };
}
	 
