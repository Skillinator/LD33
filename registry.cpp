#include "skilLib.h"
#include <string.h>

Registry::Registry(){

}

bool Registry::register(Component* c, std::string name){
  for(int x = 0; x < components.size(); x++){
    if(name.compare(names.at(x)) == 0){
      return false;
    }
  }
  components.push_back(c);
}

Component* getComponent(std::string name){

}
