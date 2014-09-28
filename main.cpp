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

int main(){
    std::cout<<"Loaded SkilLib v" << libVersion << "\n";
    theEngine = new Engine();
    theEngine->addSystem(new WindowSystem(1024, 720, "RTS-CTF CONCEPT"));
    theEngine->addSystem(new TimekeeperSystem());
	theEngine->addSystem(new MovementSystem());
    theEngine->addSystem(new RenderSystem());
    
   	Entity* tmp = new Entity();
   	tmp->addComponent(new Color(1.0, 0.0, 0.0, 1.0));
   	tmp->addComponent(new Dimensions(64, 32));
   	tmp->addComponent(new Position(0, 128));

	  tmp->addComponent(new Vector(100.0, 0.0, COMPONENT_VELOCITY));
   	theEngine-> addEntity(tmp);

   	theEngine->start();

}

