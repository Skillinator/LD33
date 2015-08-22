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
	ufox = 0;
	ufoy = 0;
	toggleBeam = false;
	toggleEngine = false;
	beamActive = false;
	engineActive = false;
}


void UFOParticleSystem::update(float delta){

	

	for(int iterator = 0; iterator < numEntities(); iterator++){
    
    	Entity *ent = entityAt(iterator);
    

	    if(ent->hasComponent(LD33_ISUFOCOMPONENT)){
	    	engineActive = ent->hasComponent(LD33_UFOFLYINGCOMPONENT);
	    	beamActive = ent->hasComponent(LD33_UFOBEAMINGCOMPONENT);
	    	Position* pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));

	    	ufox = pos->getX();
	    	ufoy = pos->getY();
	    }


		if(engineActive && !toggleEngine){
			Entity *tmpBurner = new Entity();
			tmpBurner->addComponent(new Position(ufox, ufoy-5, -1));
			tmpBurner->addComponent(new Dimensions(18, 11));
			tmpBurner->addComponent(new Color(.85, 0, 0, .4));
			tmpBurner->addComponent(new Property(LD33_UFOENGINEEFFECTCOMPONENT));
			theEngine->addEntity(tmpBurner);


			Entity *tmpBurner2 = new Entity();
			tmpBurner2->addComponent(new Position(ufox, ufoy-5, -1));
			tmpBurner2->addComponent(new Dimensions(12, 8));
			tmpBurner2->addComponent(new Color(.85, .85, 0, .6));
			tmpBurner2->addComponent(new Property(LD33_UFOENGINEEFFECTCOMPONENT));
			theEngine->addEntity(tmpBurner2);
		}

		if(beamActive && !toggleBeam){
			Entity *tmpBurner = new Entity();
			tmpBurner->addComponent(new Position(ufox, ufoy-32, -1));
			tmpBurner->addComponent(new Dimensions(18, 64));
			tmpBurner->addComponent(new Color(.25, .85, 1, .4));
			tmpBurner->addComponent(new Property(LD33_UFOBEAMEFFECTCOMPONENT));
			theEngine->addEntity(tmpBurner);
		}

		toggleEngine = engineActive;
		toggleBeam = beamActive;
    	
	    if(ent->hasComponent(LD33_UFOBEAMEFFECTCOMPONENT) && !beamActive){
	    	theEngine->removeEntity(iterator);
	    	iterator--;
	    }

	    if(ent->hasComponent(LD33_UFOENGINEEFFECTCOMPONENT)){
	    	Position *pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));
	    	pos->setX(ufox);
	    	pos->setY(ufoy-5);
	    }

	    if(ent->hasComponent(LD33_UFOENGINEEFFECTCOMPONENT) && !engineActive){
			std::cout<<"Removed Engine";
			theEngine->removeEntity(iterator);
	    	iterator--;
	    }
 	}
}
	 
