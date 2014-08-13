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

Velocity::Velocity(){
	id = COMPONENT_VELOCITY;
	magnitude = 0.0;
	direction = 0.0;
}

Velocity::Velocity(float gmag, float gdir){
	id = COMPONENT_VELOCITY;
	magnitude = gmag;
	direction = gdir;
}
