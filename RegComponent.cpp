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

/*
This IS NOT a typical component!!! This is merely the registry 
wrapper for a component, its name, and its signatures.
*/

RegComponent::RegComponent(){
	name = "null";
	signatures.push_back("ERR");
	seed = new NullComponent();
}

RegComponent::RegComponent(std::string gName, std::vector<std::string> gSignatures){
	name = gName;
	signatures = gSignatures;
	seed = new NullComponent(); // Registry needs components to register, seed will be replaced.
}



void RegComponent::consoleDump(){
  std::cout<<"Component. Name: " << name << " Address: " <<this<< "\n";
  std::cout<<"Sources: ";
  for(int x = 0; x < signatures.size(); x++){
  	std::cout<<signatures[x]<<" ";	
  }
  std::cout<<"\n===================================================\n";
}