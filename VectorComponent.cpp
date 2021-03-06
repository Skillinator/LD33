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

const float PI = 3.141592654;

Vector::Vector(){
	id = COMPONENT_VECTOR;
	magnitude = 0.0;
	direction = 0.0;
	updateComponents();
}

Vector::Vector(float gmag, float gdir){
	id = COMPONENT_VECTOR;
	magnitude = gmag;
	direction = gdir;
	updateComponents();
}

Vector::Vector(float gmag, float gdir, int gid){
	id = gid;
	magnitude = gmag;
	direction = gdir;
	updateComponents();
}

Component *Vector::spawn(std::string sig, std::string args){
	std::vector<std::string> arguments = split(args, ' ');
	arguments.erase(arguments.begin());

	if(sig.compare("ff") == 0){
		return new Vector(stof(arguments[0]), stof(arguments[1]));
	}else if(sig.compare("ffi") == 0){
		return new Vector(stof(arguments[0]), stof(arguments[1]), stoi(arguments[2]));
	}else if(sig.compare("ffs") == 0){
		int type = 0;
		if(arguments[2].compare("velocity") == 0){
			type = COMPONENT_VELOCITY;
		}
		if(arguments[2].compare("acceleration") == 0){
			type = COMPONENT_ACCELERATION;
		}
		if(arguments[2].compare("angularVelocity") == 0){
			type = COMPONENT_ANGULARVELOCITY;
		}
		return new Vector(stof(arguments[0]), stof(arguments[1]), type);
	}
	return new Vector();
}

void Vector::updateComponents(){
	xComponent = magnitude * cos(direction);
	yComponent = magnitude * sin(direction);
}

void Vector::updateDirection(){
	direction = atan(yComponent/xComponent);
	if(xComponent < 0)
		direction += PI;

	if(direction > 2*PI)
		direction -= 2*PI;
	
	magnitude = sqrt(pow(xComponent,2) + pow(yComponent,2));
}

void Vector::add(Vector vec2){
	xComponent += vec2.getMagnitude() * cos(vec2.getDirection());
	yComponent += vec2.getMagnitude() * sin(vec2.getDirection());
	updateDirection();
}

void Vector::setXComponent(float x){ xComponent = x; updateDirection(); }
void Vector::setYComponent(float y){ yComponent = y; updateDirection(); }

void Vector::setMagnitude(float gmag){ magnitude = gmag; updateComponents(); }

void Vector::setDirection(float gdir){ direction = gdir; updateComponents(); }

float Vector::getMagnitude(){ return magnitude; }
float Vector::getDirection(){ return direction; }
float Vector::getXComponent(){ return xComponent; }
float Vector::getYComponent(){ return yComponent; }