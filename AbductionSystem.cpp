

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
	handler = new AbductionSystemHandler();
	ufox = ufoy = progress = 0;
	beam = false;
	currentAbductee = new Entity();
	slot1 = slot2 = slot3 = slot4 = slot5 = false;
}

float abductSpeed = 10;

Entity* buttonFactory(float x, float y, float r, float g, float b, std::string text, std::string message, int place){
	Entity *tmp = new Entity();
	tmp->addComponent(new Position(x, y, 5));
	tmp->addComponent(new Color(r,g,b,1));
	tmp->addComponent(new TextMessage(text, "fixedWhite", 12, -30));
	tmp->addComponent(new Dimensions(60, 24));
	tmp->addComponent(new StringMessageOnClick(message));

	int property;

	switch(place){
		case 1: property = LD33_PLACEONE; break;
		case 2: property = LD33_PLACETWO; break;
		case 3: property = LD33_PLACETHREE; break;
		case 4: property = LD33_PLACEFOUR; break;
		case 5: property = LD33_PLACEFIVE; break;
	}
	tmp->addComponent(new Property(property));

	return tmp;
}

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
			slot1 = true;
			currentAbductee->addComponent(new Property(LD33_PLACEONE));
		}else if(!slot2){
			slot2 = true;
			place = 2;
			currentAbductee->addComponent(new Property(LD33_PLACETWO));
		}else if(!slot3){
			slot3 = true;
			place = 3;
			currentAbductee->addComponent(new Property(LD33_PLACETHREE));
		}else if(!slot4){
			slot4 = true;
			place = 4;
			currentAbductee->addComponent(new Property(LD33_PLACEFOUR));
		}else if(!slot5){
			slot5 = true;
			place = 5;
			currentAbductee->addComponent(new Property(LD33_PLACEFIVE));
		}else{
			placeable = false;
		}

		static_cast<Vector*>(currentAbductee->getComponent(COMPONENT_VELOCITY))->setYComponent(0);
		
		if(placeable){
			currentAbductee->removeComponent(COMPONENT_SCROLL);
			Position* pos = static_cast<Position *>(currentAbductee->getComponent(COMPONENT_POSITION));
			pos->setY(655);
			pos->setX(320+150*(place-1));
			pos->setZ(3);

			if(currentAbductee->hasComponent(LD33_RELEASABLECOMPONENT))
				theEngine->addEntity(buttonFactory(320+150*(place-1)-30, 625, 0.1, 0.6, 0.2, "Release", "Release"+std::to_string(place), place));

			if(currentAbductee->hasComponent(LD33_BRAINWASHABLECOMPONENT))
				theEngine->addEntity(buttonFactory(320+150*(place-1)+30, 625, 1.0, 0.0, 0.0, "Brainwash", "Brainwash"+std::to_string(place), place));
			
			if(currentAbductee->hasComponent(LD33_EMPLOYABLECOMPONENT))
				theEngine->addEntity(buttonFactory(320+150*(place-1)+30, 625, 0.0, 0.0, 0.7, "Employ", "Employ"+std::to_string(place), place));

			if(currentAbductee->hasComponent(LD33_WINPROGRESS))
				messageSystems(new StringMessage("WINPROGRESS"));
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
	 
