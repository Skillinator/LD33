#include "skilLib.h"
#include "components.h"
#include <string>
#include <iostream>

Property::Property(){
  id = COMPONENT_PROPERTY;
}

Property::Property(int gID){
  id = gID;
}

Component *Property::spawn(std::string sig, std::string args){
  return new Property(id);
}
