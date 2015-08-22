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
      int speed = 20;
      int vertical, horizontal;
      vertical = horizontal = 0;

      w = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
      a = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
      s = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
      d = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
      space = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
      shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);

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
      std::cout<<horizontal<<":"<<vertical<<"\n";

      if(!ent->hasComponent(LD33_UFOFLYINGCOMPONENT))
        horizontal = vertical = 0;

      std::cout<<horizontal<<":"<<vertical<<"\n";

      vel->setXComponent(horizontal);
      vel->setYComponent(vertical);



    }
    
  }
}
	 
