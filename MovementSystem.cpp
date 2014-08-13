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
#include <math.h>

MovementSystem::MovementSystem(){
	id = SYSTEM_MOVEMENT;
}

void MovementSystem::update(float delta){
	for(int x = 0; x < numEntities(); x++){
		Entity* ent = entityAt(x);
		if(ent->hasComponent(COMPONENT_POSITION) && ent->hasComponent(COMPONENT_VELOCITY)){
			Position *pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));
			Velocity *vel = static_cast<Velocity*>(ent->getComponent(COMPONENT_VELOCITY));
			
			float x = pos->getX();
			float y = pos->getY();
			float mag = vel->getMagnitude();
			float dir = vel->getDirection();
			
			float xchange = (mag * delta) * cos(dir);
			std::cout << "(" << mag << "*" << delta << ") * cos(" << dir << ") = " << xchange << "\n";
			float ychange = (mag * delta) * sin(dir);
			
			pos->setX(x+xchange);
			pos->setY(y+ychange);
		}
	}
}