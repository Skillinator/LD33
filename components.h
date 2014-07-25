#ifndef _skilLibComponents
#define _skilLibComponents

#include <stdio.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <string>
#include "skilLib.h"
#include "systems.h"
#include "messages.h"

const int COMPONENT_COLOR = 1;
const int COMPONENT_POSITION = 2;
const int COMPONENT_DIMENSIONS = 3;
const int COMPONENT_TEXTURE = 4; //not yet iomplemented
class Color : public Component{
public:
	Color();
	Color(float gr, float gg, float gb);
	float getR();
	float getG();
	float getB();
	void setR(float get);
	void setG(float get);
	void setB(float get);
protected:
	float r, g, b;
};

class Position : public Component{
public:
	Position();
	Position(float gx, float gy);
	float getX();
	float getY();
	void setX(float get);
	void setY(float get);
protected:
	float x, y;
};

class Dimensions : public Component{
public:
	Dimensions();
	Dimensions(int gw, int gh);
	int getWidth();
	int getHeight();
	void setWidth(int get);
	void setHeight(int get);
public:
	int width, height;
};
#endif
