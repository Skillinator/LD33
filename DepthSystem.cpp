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

DepthSystem::DepthSystem(){
	id = SYSTEM_DEPTH;
}

void DepthSystem::update(float delta){
	bool isSorted = false;

	while(!isSorted){
		isSorted = true;

		for(int i = 0; i < theEngine->numEntities()-1; i++){
			Entity *ent1 = theEngine->getEntity(i);
			Entity *ent2 = theEngine->getEntity(i+1);

			int z1, z2;;

			if(ent1->hasComponent(COMPONENT_POSITION)){
				z1 = static_cast<Position*>(ent1->getComponent(COMPONENT_POSITION))->getZ();
			}else{
				// Surely we'll never have more entities than that, right?
				z1 = -9001;
			}

			if(ent2->hasComponent(COMPONENT_POSITION)){
				z2 = static_cast<Position*>(ent2->getComponent(COMPONENT_POSITION))->getZ();
			}else{
				// Surely we'll never have more entities than that, right?
				z2 = -9001;
			}

			if(z1 > z2){
				theEngine->removeEntity(i);
				theEngine->addEntity(ent1);
				isSorted = false;
			}
		}
	}
}