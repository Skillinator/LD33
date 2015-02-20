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

int windowheight = 736;
int windowwidth = 736;
std::string title = "RTS-CTF-CONCEPT";
double libVersion = 0.1;


GLFWwindow* window;
/*
void GLFWCALL windowResize(int getwidth, int getheight){
    windowheight=getheight;
    windowwidth=getwidth;
}
*/


Engine *theEngine;

void buildRegistry(){
	//At least some of this is temporary, and will become replaced after XML Loading is implemented. 
	
	/*
	Load Component Color
	*/
    std::vector<std::string> colorSigs;
    colorSigs.push_back("ffff");
    theEngine->registry.declare("color", colorSigs);
    Component *tmpColor = new Color();
    theEngine->registry.Register(tmpColor, "color");
	
	/*
	Load Component Position
	*/
	std::vector<std::string> posSigs;
	posSigs.push_back("ff");
	theEngine->registry.declare("position", posSigs);
	Component *tmpPos = new Position();
	theEngine->registry.Register(tmpPos, "position");
	
	/*
	Load Component Dimensions
	*/
	std::vector<std::string> dimSigs;
	dimSigs.push_back("ii");
	theEngine->registry.declare("dimensions", dimSigs);
	Component *tmpDim = new Dimensions();
	theEngine->registry.Register(tmpDim, "dimensions");
	
	/*
	Load Component Vector
	*/
	std::vector<std::string> vectorSigs;
	vectorSigs.push_back("ff");
	vectorSigs.push_back("ffi");
	theEngine->registry.declare("vector", vectorSigs);
	Component *tmpVec = new Vector();
	theEngine->registry.Register(tmpVec, "vector");
}


int main(){
    
    std::cout<<"Loaded SkilLib v" << libVersion << "\n";
    theEngine = new Engine();
    theEngine->addSystem(new WindowSystem(1024, 720, "RTS-CTF CONCEPT"));
    theEngine->addSystem(new TimekeeperSystem());
    theEngine->addSystem(new MovementSystem());
    theEngine->addSystem(new RenderSystem());
	
	buildRegistry();
	

    Entity* tmp = new Entity();

   	tmp->addComponent(engine->registry.getComponent("color 1.0 0.0 0.0 1.0"));
   	tmp->addComponent(engine->registry.getComponent("dimensions 64 32"));
   	tmp->addComponent(engine->registry.getComponent("position 0 128"));
	tmp->addComponent(engine->registry.getComponent("vector 100.0 0.0 " + COMPONENT_VELOCITY));
   	theEngine-> addEntity(tmp);

   	theEngine->start();
    
}

