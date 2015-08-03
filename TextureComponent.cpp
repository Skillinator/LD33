#include "skilLib.h"
#include "components.h"
#include <string>
#include <iostream>

Texture::Texture(){
  id = COMPONENT_TEXTURE;
  tex = getRegistry()->getTextureMapped("default");
}

Texture::Texture(std::string name){
  id = COMPONENT_TEXTURE;
  tex = getRegistry()->getTextureMapped(name);
}

Component *Texture::spawn(std::string sig, std::string args){
  std::vector<std::string> arguments = split(args, ' ');
  arguments.erase(arguments.begin());
  if(sig.compare("s") == 0){
    return new Texture(arguments[0]);
  }
  return new Texture();
}
