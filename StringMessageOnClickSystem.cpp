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
extern bool final;

StringMessageOnClickSystem::StringMessageOnClickSystem(){
	id = SYSTEM_STRINGMESSAGEONCLICK;
}

void StringMessageOnClickSystem::update(float delta){
  for(int iterator = 0; iterator < numEntities(); iterator++){
    Entity *ent = entityAt(iterator);

    if(ent->hasComponent(COMPONENT_STRINGMESSAGEONCLICK)){
      StringMessageOnClick *smoc = static_cast<StringMessageOnClick*>(ent->getComponent(COMPONENT_STRINGMESSAGEONCLICK));
      Position *pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));
      Dimensions *dim = static_cast<Dimensions*>(ent->getComponent(COMPONENT_DIMENSIONS));

      double mousex;
      double mousey;
      glfwGetCursorPos(window, &mousex,&mousey);
      mousey = windowheight - mousey;

      bool clicked = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS);

      if(clicked){
        if(!final){
          std::cout<<"("<<mousex<<","<<mousey<<")\n";
          std::cout<<"("<<pos->getX()<<","<<pos->getY()<<")\n\n";
        }
        if(mousex > pos->getX() - dim->getWidth()/2 && mousex < pos->getX()+dim->getWidth()/2){
          if(mousey > pos->getY() - dim->getHeight()/2 && mousey < pos->getY()+dim->getHeight()/2){
            messageSystems(new StringMessage(smoc->message));  
          }
        }
      }

    }

  };
}
	 
