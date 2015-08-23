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
#include "ld33.h"

int windowheight = 875;
int windowwidth = 1440;
std::string title = "LD33";
double libVersion = 0.1;


GLFWwindow* window;

Engine *theEngine;

Registry* getRegistry(){
  return &(theEngine->registry);
}

void buildRegistry(){

  /*
  float xMaps[4] = {0.0, 1.0, 1.0, 0.0};
  float yMaps[4] = {0.0, 0.0, 1.0, 1.0};

  theEngine->registry.addTextureMapped("default", "default", xMaps, yMaps);
  */
  theEngine->loadXUPL("res/stockComponents.xupl");
  theEngine->loadXUPL("res/stockResources.xupl");



  theEngine->registry.Register(new Color(), "color");
  theEngine->registry.Register(new Position(), "position");
  theEngine->registry.Register(new Dimensions(), "dimensions");  
  theEngine->registry.Register(new Vector(), "vector");
  theEngine->registry.Register(new Texture(), "texture");
  theEngine->registry.Register(new TextMessage(), "textmessage");
  theEngine->registry.Register(new ClickDrag(), "clickdrag");
  theEngine->registry.Register(new Center(), "center");
  theEngine->registry.Register(new TimedMessage(), "timedmessage");
  theEngine->registry.Register(new Property(COMPONENT_SCROLL), "scroll");

  /*
  New Ludum Dare Components
  */
  theEngine->registry.Register(new Property(LD33_UFOFLYINGCOMPONENT), "ufoflying");
  theEngine->registry.Register(new Property(LD33_ISUFOCOMPONENT), "isufo");
  theEngine->registry.Register(new Property(LD33_UFOBEAMINGCOMPONENT), "ufobeaming");
  theEngine->registry.Register(new Property(LD33_UFOBEAMEFFECTCOMPONENT), "ufobeameffect");
  theEngine->registry.Register(new Property(LD33_UFOENGINEEFFECTCOMPONENT), "ufoengineeffect");
 
 
}

int main(){  
  std::cout<<"Loaded SkilLib v" << libVersion << "\n";
  theEngine = new Engine();
  theEngine->addSystem(new WindowSystem(windowwidth, windowheight, "RTS-CTF CONCEPT"));
  theEngine->addSystem(new TimekeeperSystem());
  theEngine->addSystem(new MovementSystem());
  theEngine->addSystem(new RenderSystem());
  theEngine->addSystem(new ClickDragSystem());
  theEngine->addSystem(new CenterSystem(windowwidth, windowheight));
  theEngine->addSystem(new TimedMessageSystem());
  theEngine->addSystem(new SceneSystem());
  theEngine->addSystem(new DepthSystem());
  theEngine->addSystem(new ScrollSystem(2048, 2048));


  /*
  LD33 Specific Systems
  */

  theEngine->addSystem(new UFOControlSystem());
  theEngine->addSystem(new UFOParticleSystem());

  std::cout<<"\nSystems added\n";

  theEngine->loadXUPL("res/ld33.xupl");

  buildRegistry();

  theEngine->registry.dump();
  std::cout<<"\nRegistry built\n";
  
  theEngine->loadXUPL("res/startingEntities.xupl");
	
  theEngine->start();
    
}

