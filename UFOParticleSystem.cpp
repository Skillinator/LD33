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

UFOParticleSystem::UFOParticleSystem(){
	id = LD33_UFOPARTICLESYSTEM;
}

void UFOParticleSystem::update(float delta){

  for(int iterator = 0; iterator < numEntities(); iterator++){
    
    Entity *ent = entityAt(iterator);
    
    
  }
}
	 
