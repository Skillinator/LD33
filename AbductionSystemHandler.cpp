#include <iostream>
#include <ctime>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "SOIL.h"
#include "skilLib.h"
#include "systems.h"
#include "components.h"
#include "messages.h"
#include <math.h>
#include "ld33.h"

extern Engine *theEngine;
extern float scrollx;
extern float scrolly;

AbductionSystemHandler::AbductionSystemHandler(){
	// Nothing doing
}


void AbductionSystemHandler::handle(Message *m, Entity *ent){
	
	// Nothing doing here lol
}

void AbductionSystemHandler::handle(Message *m, System *sys){
	AbductionSystem *as = static_cast<AbductionSystem*>(sys);
	if(m->messageType == MESSAGE_STRING){
		StringMessage *sm = static_cast<StringMessage*>(m);
		
		if(sm->message.find("Release") != std::string::npos){
			int place = std::stof(sm->message.substr(7));

			int property;

			switch(place){
				case 1: property = LD33_PLACEONE; break;
				case 2: property = LD33_PLACETWO; break;
				case 3: property = LD33_PLACETHREE; break;
				case 4: property = LD33_PLACEFOUR; break;
				case 5: property = LD33_PLACEFIVE; break;
			}

			float x, y;

			for(int i = 0; i < theEngine->numEntities(); i++){
				Entity* ent = theEngine->getEntity(i);

				if(ent->hasComponent(LD33_ISUFOCOMPONENT)){
					
					Position *pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));

					x = pos->getX();
					y = pos->getY();
				}
			}

			for(int i = 0; i < theEngine->numEntities(); i++){
				Entity* ent = theEngine->getEntity(i);

				if(ent->hasComponent(property)){
					
					if(ent->hasComponent(LD33_ABDUCTIBLECOMPONENT)){
						Position *pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));
						pos->setX(x);
						pos->setY(y-32);

						ent->addComponent(new Property(COMPONENT_SCROLL));
						
						if(ent->hasComponent(LD33_ISDJ) && ent->hasComponent(LD33_BRAINWASHEDCOMPONENT)){
							Entity* ent2 = new Entity();
							ent2->addComponent(new Dimensions(128, 128));
							ent2->addComponent(new Texture("book"));
							ent2->addComponent(new Property(LD33_ABDUCTIBLECOMPONENT));
							ent2->addComponent(new Property(LD33_WINPROGRESS));
							ent2->addComponent(new Position(768+scrollx, 640+scrolly));
							ent2->addComponent(new Property(COMPONENT_SCROLL));
							theEngine->addEntity(ent2);
						}

						if(ent->hasComponent(LD33_ISENGINEER) && ent->hasComponent(LD33_BRAINWASHEDCOMPONENT)){
							Entity* ent2 = new Entity();
							ent2->addComponent(new Dimensions(128, 128));
							ent2->addComponent(new Texture("fuel"));
							ent2->addComponent(new Property(LD33_ABDUCTIBLECOMPONENT));
							ent2->addComponent(new Property(LD33_WINPROGRESS));
							ent2->addComponent(new Position(1216+scrollx, 640+scrollx));
							ent2->addComponent(new Property(COMPONENT_SCROLL));
							theEngine->addEntity(ent2);
						}

					}else{
					theEngine->removeEntity(i);
					i--;
					}
					switch(place){

					case 1: as->slot1 = false; break;
					case 2: as->slot2 = false; break;
					case 3: as->slot3 = false; break;
					case 4: as->slot4 = false; break;
					case 5: as->slot5 = false; break;
					}
				}
			}
		
		}
		if(sm->message.find("Employ") != std::string::npos){
			int place = std::stof(sm->message.substr(6));

			int property;

			switch(place){
				case 1: property = LD33_PLACEONE; break;
				case 2: property = LD33_PLACETWO; break;
				case 3: property = LD33_PLACETHREE; break;
				case 4: property = LD33_PLACEFOUR; break;
				case 5: property = LD33_PLACEFIVE; break;
			}

			for(int i = 0; i < theEngine->numEntities(); i++){
				Entity* ent = theEngine->getEntity(i);

				if(ent->hasComponent(property)){
					
					if(ent->hasComponent(LD33_ABDUCTIBLECOMPONENT)){
						ent->addComponent(new Property(LD33_EMPLOYEDCOMPONENT));
						messageSystems(new StringMessage("WINPROGRESS"));
					}else{
					theEngine->removeEntity(i);
					i--;
					}
				}
			}
		
		}


		if(sm->message.find("Brainwash") != std::string::npos){
			int place = std::stof(sm->message.substr(9));

			int property;

			switch(place){
				case 1: property = LD33_PLACEONE; break;
				case 2: property = LD33_PLACETWO; break;
				case 3: property = LD33_PLACETHREE; break;
				case 4: property = LD33_PLACEFOUR; break;
				case 5: property = LD33_PLACEFIVE; break;
			}

			for(int i = 0; i < theEngine->numEntities(); i++){
				Entity* ent = theEngine->getEntity(i);

				if(ent->hasComponent(property)){
					
					if(ent->hasComponent(LD33_ABDUCTIBLECOMPONENT)){
						ent->addComponent(new Property(LD33_BRAINWASHEDCOMPONENT));
					}
				}
			}
		
		}




	}
}