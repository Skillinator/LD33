#include "skilLib.h"
#include "components.h"
#include <string>
#include <iostream>

BarGraph::BarGraph(){
	id = COMPONENT_BARGRAPH;
	gid = "nul";
	maximum = x = y = dir = ratio = 0;
}

BarGraph::BarGraph(std::string gID, float centerx, float centery, float rat, float max, float orientation){
	id = COMPONENT_BARGRAPH;
	gid = gID;
	x = centerx;
	y = centery;
	ratio = rat;
	maximum = max;
	dir = orientation;
}

Component *BarGraph::spawn(std::string sig, std::string args){
  std::vector<std::string> arguments = splitForStrings(args, ' ');
  arguments.erase(arguments.begin());
  if(sig.compare("sfffff") == 0){
    return new BarGraph(arguments[0], stof(arguments[1]), stof(arguments[2]), stof(arguments[3]), stof(arguments[4]), stof(arguments[5]));
  }
  return new BarGraph();
}
