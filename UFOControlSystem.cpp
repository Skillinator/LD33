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
extern int windowwidth;
extern int windowheight;

const float PI = 3.141592654;

bool toggleShift = false;
bool toggleSpace = false;

UFOControlSystem::UFOControlSystem(){
	id = LD33_UFOCONTROLSYSTEM;
}

void UFOControlSystem::update(float delta){

  for(int iterator = 0; iterator < numEntities(); iterator++){
    
    Entity *ent = entityAt(iterator);
    if(ent->hasComponent(LD33_ISUFOCOMPONENT) && ent->hasComponent(COMPONENT_VELOCITY)){

      Vector* vel = static_cast<Vector*>(ent->getComponent(COMPONENT_VELOCITY));
      bool w, a, s, d, space, shift;
      int speed = 150;
      int vertical, horizontal;
      vertical = horizontal = 0;

      w = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
      a = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
      s = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
      d = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
      space = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
      shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);

      if(!space)
        toggleSpace = false;

      if(space && !toggleSpace){
        if(ent->hasComponent(LD33_UFOFLYINGCOMPONENT)){
          ent->removeComponent(LD33_UFOFLYINGCOMPONENT);
        }else{
          ent->addComponent(new Property(LD33_UFOFLYINGCOMPONENT));
        }
        toggleSpace = true;
      }


      if(!shift)
        toggleShift = false;

      if(shift && !toggleShift){
        if(ent->hasComponent(LD33_UFOBEAMINGCOMPONENT)){
          ent->removeComponent(LD33_UFOBEAMINGCOMPONENT);
        }else{
          ent->addComponent(new Property(LD33_UFOBEAMINGCOMPONENT));
        }
        toggleShift = true;
      }

      if(w != s){
        if(w)
          vertical = speed;
        if(s)
          vertical = -speed;
      }

      if(a != d){
        if(a)
          horizontal = -speed;
        if(d)
          horizontal = speed;
      }

      if(!ent->hasComponent(LD33_UFOFLYINGCOMPONENT) || ent->hasComponent(LD33_UFOBEAMINGCOMPONENT))
        horizontal = vertical = 0;

      Position* pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));

      if((pos->getX() < 32 && horizontal < 0) || (pos->getX() > windowwidth-32 && horizontal > 0)){
        messageSystems(new ScrollMessage(horizontal*delta, 0));
        vel->setXComponent(0);
      }else{
        vel->setXComponent(horizontal);
      }

      if((pos->getY() < 32 && vertical < 0) || (pos->getY() > windowheight-32 && vertical > 0)){
        messageSystems(new ScrollMessage(0, vertical*delta));
        vel->setYComponent(0);
      }else{
        vel->setYComponent(vertical);
      }


    }
    
  }
}
	 
