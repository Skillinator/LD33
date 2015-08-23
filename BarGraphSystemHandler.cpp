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

extern Engine *theEngine;

BarGraphSystemHandler::BarGraphSystemHandler(){
	// Nothing doing
}


void BarGraphSystemHandler::handle(Message *m, Entity *ent){
	
	// Nothing doing here lol
}

void BarGraphSystemHandler::handle(Message *m, System *sys){
	BarGraphSystem *bgs = static_cast<BarGraphSystem*>(sys);
	if(m->messageType == MESSAGE_BARGRAPH_SET){
		SetBarGraphMessage *sg = static_cast<SetBarGraphMessage*>(m);
		
		for(int i = 0; i < theEngine->numEntities(); i++){
			Entity* ent = theEngine->getEntity(i);

			if(ent->hasComponent(COMPONENT_BARGRAPH) && ent->hasComponent(COMPONENT_DIMENSIONS) && ent->hasComponent(COMPONENT_POSITION)){
				
				BarGraph* bar = static_cast<BarGraph*>(ent->getComponent(COMPONENT_BARGRAPH));
				
				if(bar->gid == sg->target){

					Position* pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));
					Dimensions* dim = static_cast<Dimensions*>(ent->getComponent(COMPONENT_DIMENSIONS));
					
					float length = sg->value * bar->ratio;

					dim->setWidth(length);

					pos->setX(bar->x - bar->maximum/2 + length/2);

				}
			}
		}


	}

	if(m->messageType == MESSAGE_BARGRAPH_CHANGE){
		ChangeBarGraphMessage *sg = static_cast<ChangeBarGraphMessage*>(m);

		for(int i = 0; i < theEngine->numEntities(); i++){
			Entity* ent = theEngine->getEntity(i);
			
			if(ent->hasComponent(COMPONENT_BARGRAPH) && ent->hasComponent(COMPONENT_DIMENSIONS) && ent->hasComponent(COMPONENT_POSITION)){
				
				BarGraph* bar = static_cast<BarGraph*>(ent->getComponent(COMPONENT_BARGRAPH));
				
				if(bar->gid == sg->target){

					Position* pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));
					Dimensions* dim = static_cast<Dimensions*>(ent->getComponent(COMPONENT_DIMENSIONS));
					
					float length = dim->getWidth() + sg->change * bar->ratio;
					if(length > bar->maximum)
						length = bar->maximum;

					dim->setWidth(length);

					pos->setX(bar->x - bar->maximum/2 + length/2);

				}
			}
		}
		

	}
}