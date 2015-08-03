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

NullComponent::NullComponent(){
	id = COMPONENT_NONE;
}

Component* NullComponent::spawn(std::string sig, std::string args){
	return new NullComponent();
}