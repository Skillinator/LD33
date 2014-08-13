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

RenderSystem::RenderSystem(){
	id = SYSTEM_RENDER;
}

void RenderSystem::update(float delta){
	// we don't need to implement this yet, let's get things compiling first
	for(int x = 0; x < numEntities(); x++){
		Entity *ent = entityAt(x);
		if(ent->hasComponent(COMPONENT_POSITION) && ent->hasComponent(COMPONENT_DIMENSIONS) && ent->hasComponent(COMPONENT_COLOR)){
			Color* color = static_cast<Color*>(ent->getComponent(COMPONENT_COLOR));
			Dimensions *dim = static_cast<Dimensions*>(ent->getComponent(COMPONENT_DIMENSIONS));
			Position *pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));

			int x = pos->getX();
			int y = pos->getY();
			int w = dim->getWidth();
			int h = dim->getHeight();
			float r = color->getR();
			float g = color->getG();
			float b = color->getB();
			float a = color->getA();
			glDisable(GL_TEXTURE_2D);
			glColor4f(r,g,b,a);
			glBegin(GL_QUADS);
				glVertex2i(x,y);
				glVertex2i(x+w,y);
				glVertex2i(x+w,y+h);
				glVertex2i(x,y+h);
			glEnd();
			glColor3f(1.0, 1.0, 1.0);

		}
	}
}