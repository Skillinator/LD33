

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
extern int windowheight;

AbductionSystem::AbductionSystem(){
	id = LD33_ABDUCTIONSYSTEM;
	ufox = ufoy = progress = 0;
	beam = false;
	currentAbductee = new Entity();
	slot1 = slot2 = slot3 = slot4 = slot5 = false;
}

float abductSpeed = 10;

void AbductionSystem::update(float delta){
	if(!beam){
		if(currentAbductee->hasComponent(COMPONENT_POSITION)){
			Position* pos = static_cast<Position *>(currentAbductee->getComponent(COMPONENT_POSITION));
			pos->setY(pos->getY() - progress*abductSpeed);
		}

		if(currentAbductee->hasComponent(COMPONENT_VELOCITY))
			static_cast<Vector*>(currentAbductee->getComponent(COMPONENT_VELOCITY))->setYComponent(0);
		
		currentAbductee = new Entity();
		progress = 0;
	}
	
	if(progress > 2.5){
		bool placeable = true;
		int place;
		if(!slot1){
			place = 1;
		}else if(!slot2){
			place = 2;
		}else if(!slot3){
			place = 3;
		}else if(!slot4){
			place = 4;
		}else if(!slot5){
			place = 5;
		}else{
			placeable = false;
		}

		static_cast<Vector*>(currentAbductee->getComponent(COMPONENT_VELOCITY))->setYComponent(0);
		
		if(placeable){
			Position* pos = static_cast<Position *>(currentAbductee->getComponent(COMPONENT_POSITION));
			pos->setY(655);
			pos->setX(320+150*(place-1));
			pos->setZ(3);
			currentAbductee = new Entity();
		}
		progress = 0;
		return;
	}
	

  for(int iterator = 0; iterator < numEntities(); iterator++){
    Entity *ent = entityAt(iterator);

    if(ent->hasComponent(LD33_ISUFOCOMPONENT)){
    	beam = ent->hasComponent(LD33_UFOBEAMINGCOMPONENT);

    	if(ent->hasComponent(COMPONENT_POSITION)){
    		Position* pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));
    		ufox = pos->getX();
    		ufoy = pos->getY();
    	}
    }



    if(ent->hasComponent(LD33_ABDUCTIBLECOMPONENT) && beam){
    	if(ent->hasComponent(COMPONENT_POSITION)){
			Position* pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));
			
			int x = pos->getX();
			int y = pos->getY();

			if(abs(x-ufox) < 40 && y < ufoy && y > ufoy-64){

		    	currentAbductee = ent;
		 		if(ent->hasComponent(COMPONENT_VELOCITY)){
		 			static_cast<Vector*>(currentAbductee->getComponent(COMPONENT_VELOCITY))->setYComponent(abductSpeed);
		    		static_cast<Vector*>(currentAbductee->getComponent(COMPONENT_VELOCITY))->setXComponent(0);
		    	}else{
		    		ent->addComponent(new Vector(abductSpeed, 3.14159/2.0, COMPONENT_VELOCITY));
		    	}
		    	progress += delta;

			}
    	}
    }

  };
}
	 
