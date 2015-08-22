#include "skilLib.h"
#include "components.h"
#include <string>
#include <iostream>

Center::Center(){
  id = COMPONENT_CENTER;
  horizontal = vertical = false;
}

Center::Center(bool h, bool v){
  id = COMPONENT_CENTER;
  horizontal = h;
  vertical = v;
}

bool Center::getHorizontal(){ return horizontal; }
bool Center::getVertical(){ return vertical; }
void Center::setHorizontal(bool h){ horizontal = h; }
void Center::setVertical(bool v){ vertical = v; }

Component *Center::spawn(std::string sig, std::string args){
  std::vector<std::string> arguments = split(args, ' ');
  arguments.erase(arguments.begin());
  if(sig.compare("bb") == 0){
    bool h, v;

    h = (arguments[0].compare("true") == 0);
    v = (arguments[1].compare("true") == 0);

    return new Center(h, v);
  }
  return new Center();
}
