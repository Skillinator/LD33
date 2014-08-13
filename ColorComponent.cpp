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

Color::Color(){
	r = g = b = 0.0;
	a = 1.0;
	id = COMPONENT_COLOR;	
}
Color::Color(float gr, float gg, float gb, float ga){
	r = gr;
	g = gg;
	b = gb;
	a = ga;
	id = COMPONENT_COLOR;	
}

float Color::getR(){ return r; }
float Color::getG(){ return g; }
float Color::getB(){ return b; }
float Color::getA(){ return a; }

void Color::setR(float get){ r = get; }
void Color::setG(float get){ g = get; }
void Color::setB(float get){ b = get; }
void Color::setA(float get){ a = get; }