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

int windowheight = 720;
int windowwidth = 1280;
std::string title = "LD33";
double libVersion = 0.1;


GLFWwindow* window;

Engine *theEngine;

bool final = false;

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
  theEngine->registry.Register(new BarGraph(), "bargraph");
  theEngine->registry.Register(new StringMessageOnClick(), "stringmessageonclick");


  /*
  New Ludum Dare Components
  */
  theEngine->registry.Register(new Property(LD33_UFOFLYINGCOMPONENT), "ufoflying");
  theEngine->registry.Register(new Property(LD33_ISUFOCOMPONENT), "isufo");
  theEngine->registry.Register(new Property(LD33_UFOBEAMINGCOMPONENT), "ufobeaming");
  theEngine->registry.Register(new Property(LD33_UFOBEAMEFFECTCOMPONENT), "ufobeameffect");
  theEngine->registry.Register(new Property(LD33_UFOENGINEEFFECTCOMPONENT), "ufoengineeffect");
  theEngine->registry.Register(new Property(LD33_ABDUCTIBLECOMPONENT), "abductible");
  
  theEngine->registry.Register(new Property(LD33_BRAINWASHABLECOMPONENT), "brainwashable");
  theEngine->registry.Register(new Property(LD33_BRAINWASHEDCOMPONENT), "brainwashed");
  theEngine->registry.Register(new Property(LD33_RELEASABLECOMPONENT), "releasable");
  theEngine->registry.Register(new Property(LD33_EMPLOYABLECOMPONENT), "employable");
  theEngine->registry.Register(new Property(LD33_EMPLOYEDCOMPONENT), "employed");
  theEngine->registry.Register(new Property(LD33_WINPROGRESS), "winprogress");
  theEngine->registry.Register(new Property(LD33_ISENGINEER), "isengineer");
  theEngine->registry.Register(new Property(LD33_ISDJ), "isdj");
 

}

int main(){  
  if(!final){
    windowheight = 860;
  }
  std::cout<<"Loaded SkilLib v" << libVersion << "\n";
  theEngine = new Engine();
  theEngine->addSystem(new WindowSystem(windowwidth, windowheight, title));
  theEngine->addSystem(new TimekeeperSystem());
  theEngine->addSystem(new MovementSystem());
  theEngine->addSystem(new RenderSystem());
  theEngine->addSystem(new ClickDragSystem());
  theEngine->addSystem(new CenterSystem(windowwidth, windowheight));
  theEngine->addSystem(new TimedMessageSystem());
  theEngine->addSystem(new SceneSystem());
  theEngine->addSystem(new DepthSystem());
  theEngine->addSystem(new ScrollSystem(2048, 2048));
  theEngine->addSystem(new BarGraphSystem());
  theEngine->addSystem(new StringMessageOnClickSystem());

  /*
  LD33 Specific Systems
  */

  theEngine->addSystem(new UFOControlSystem());
  theEngine->addSystem(new UFOParticleSystem());
  theEngine->addSystem(new AbductionSystem());
  theEngine->addSystem(new WinLossSystem());

  std::cout<<"\nSystems added\n";

  theEngine->loadXUPL("res/ld33.xupl");

  buildRegistry();

  std::cout<<"\nRegistry built\n";
  
  theEngine->loadXUPL("res/startingEntities.xupl");
	
  theEngine->start();
    
}

