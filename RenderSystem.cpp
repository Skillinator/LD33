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

RenderSystem::RenderSystem(){
	id = SYSTEM_RENDER;
}

bool SHOW_VECTORS = true;

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

			if(ent->hasComponent(COMPONENT_VELOCITY) && SHOW_VECTORS){
				Vector *vel = static_cast<Vector*>(ent->getComponent(COMPONENT_VELOCITY));
				float direction = vel->getDirection();

				glDisable(GL_TEXTURE_2D);
				glColor4f(0.0, 0.0, 1.0, 1.0);

				float centerx = x+w/2;
				float centery = y+h/2;

				float endx = centerx + vel->getXComponent();
				float endy = centery + vel->getYComponent();
				glBegin(GL_TRIANGLE_FAN);
				glVertex2f(centerx, centery);

				for(int theta = 0; theta < 360; theta += 5){
					glVertex2f(centerx+sin(theta*3.14/180) * 5, centery + cos(theta*3.14/180) * 5);
				}
				glEnd();
				glLineWidth(2.0);

				glBegin(GL_LINES);
					glVertex2f(centerx, centery);
					glVertex2f(endx, endy);
				glEnd();

				float offset = 5*3.14/6;

				glBegin(GL_LINES);
					glVertex2f(endx, endy);
					glVertex2f(endx+10*cos(direction+offset), endy+10*sin(direction+offset));
				glEnd();

				glBegin(GL_LINES);
					glVertex2f(endx, endy);
					glVertex2f(endx+10*cos(direction-offset), endy+10*sin(direction-offset));
				glEnd();

			}

			glColor3f(1.0, 1.0, 1.0);

		}
	}
}
