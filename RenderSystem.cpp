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

int renderMode(Entity* ent){
  /*
    0 - Error, do nothing
    1 - Wireframe
    2 - Color
    3 - Texture
   */

  if(ent->hasComponent(COMPONENT_POSITION) && ent->hasComponent(COMPONENT_DIMENSIONS){
      if(ent->hasComponent(COMPONENT_COLOR) return 2;
      if(ent->hasComponent(COMPONENT_TEXTURE) return 3;
      return 1;
  return 0;
}

void RenderSystem::update(float delta){
  for(int x = 0; x < numEntities(); x++){
    
    Entity *ent = entityAt(x);
    int mode = renderMode(ent);
    Color* color;
    Dimensions* dim;
    Position* pos;
    Texture* tex;
    
    int x, y, w, h;
    
    if(mode > 0){
      dim = static_cast<Dimensions*>(ent->getComponent(COMPONENT_DIMENSIONS));
      pos = static_cast<Position*>(ent->getComponent(COMPONENT_POSITION));
      x = pos->getX();
      y = pos->getY();
      w = dim->getWidth();
      h = dim->getHeight();
      
    }else{
      x = y = w = h = 0;
    }

    if(mode == 2){
      color = static_cast<Color*>(ent->getComponent(COMPONENT_COLOR));
      float r = color->getR();
      float g = color->getG();
      float b = color->getB();
      float a = color->getA();
      
      glDisable(GL_TEXTURE_2D);
      glColor4f(r,g,b,a);
      glBegin(GL_QUADS);
      
      glVertex2i(x,y);
      glVertex2i(x+w, y);
      glVertex2i(x+w, y+h);
      glVertex2i(x, y+h);
      
      glEnd();
    }
    
    if(mode == 3){
      tex = static_cast<Texture*>(ent->getComponent(COMPONENT_TEXTURE));
    }

    /*
      If vectors showing for debug purposes
     */
		
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
	 
