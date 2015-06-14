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

Registry* getRegistry(){
  return &(theEngine->registry);
}

void buildRegistry(){
  theEngine->loadXUPL("res/stockComponents.xupl");
  theEngine->loadXUPL("res/stockResources.xupl");

  theEngine->registry.Register(new Color(), "color");
  theEngine->registry.Register(new Position(), "position");
  theEngine->registry.Register(new Dimensions(), "dimensions");  
  theEngine->registry.Register(new Vector(), "vector");
  theEngine->registry.Register(new Texture(), "texture");

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
  
  tmp->addComponent(theEngine->registry.getComponent("texture align"));
  tmp->addComponent(theEngine->registry.getComponent("dimensions 64 32"));
  tmp->addComponent(theEngine->registry.getComponent("position 0 128"));
  tmp->addComponent(theEngine->registry.getComponent("vector 300.0 1.0 " + std::to_string(COMPONENT_VELOCITY)));
  tmp->addComponent(theEngine->registry.getComponent("vector 100.0 4.7 " + std::to_string(COMPONENT_ACCELERATION)));
  theEngine-> addEntity(tmp);

  theEngine->start();
    
}

