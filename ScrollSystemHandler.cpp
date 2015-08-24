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
float scrollx;
float scrolly;
ScrollSystemHandler::ScrollSystemHandler(){
	// Nothing doing
}


void ScrollSystemHandler::handle(Message *m, Entity *ent){
	
	// Nothing doing here lol
}

void ScrollSystemHandler::handle(Message *m, System *sys){
	ScrollSystem *ss = static_cast<ScrollSystem*>(sys);
	if(m->messageType == MESSAGE_SCROLL){
		ScrollMessage *sm = static_cast<ScrollMessage*>(m);
		
		float cx = sm->changex;
		float cy = sm->changey;
		scrollx -=cx;
		scrolly -=cy;

		for(int i = 0; i < theEngine->numEntities(); i++){
			Entity* ent = theEngine->getEntity(i);
			if(ent->hasComponent(COMPONENT_SCROLL) && ent->hasComponent(COMPONENT_POSITION)){
				Position* pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));

				pos->setX(pos->getX() - cx);
				pos->setY(pos->getY() - cy);
			}
		}

	}
}