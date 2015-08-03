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

ClickDragSystem::ClickDragSystem(){
	id = SYSTEM_CLICKDRAG;
}

void ClickDragSystem::update(float delta){
  for(int iterator = 0; iterator < numEntities(); iterator++){
    Entity *ent = entityAt(iterator);

    if(ent->hasComponent(COMPONENT_POSITION) && ent->hasComponent(COMPONENT_DIMENSIONS) && ent->hasComponent(COMPONENT_CLICKDRAG)){
      ClickDrag *cd = static_cast<ClickDrag*>(ent->getComponent(COMPONENT_CLICKDRAG));
      Position *pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));
      Dimensions *dim = static_cast<Dimensions*>(ent->getComponent(COMPONENT_DIMENSIONS));

      bool active = cd->getActive();

      double mousex;
      double mousey;
      glfwGetCursorPos(window, &mousex,&mousey);
      mousey = windowheight - mousey;

      bool clicked = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS);

      if(!active && clicked){
        if(mousex > pos->getX() - dim->getWidth()/2 && mousex < pos->getX()+dim->getWidth()/2){
          if(mousey > pos->getY() - dim->getHeight()/2 && mousey < pos->getY()+dim->getHeight()/2){
            cd->initiate(pos->getX() - mousex, pos->getY() - mousey);
            active = true;   
          }
        }
      }

      if(active&&clicked){
        pos->setX(mousex + cd->getXOffset());
        pos->setY(mousey + cd->getYOffset());
      }

      if(active && !clicked){
        cd->release();
      }

    }

  };
}
	 
