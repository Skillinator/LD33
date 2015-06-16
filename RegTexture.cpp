#include <iostream>
#include <stdio.h>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SOIL.h"
#include "skilLib.h"

RegTexture::RegTexture(std::string gName){
  name = gName;
   texture = SOIL_load_OGL_texture
    (
      "res/defaultTexture.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT

     );
}

RegTexture::RegTexture(std::string gName, std::string path){
  name = gName.c_str();
  const char* s = path.c_str();

  texture = SOIL_load_OGL_texture
    (
     s,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
  
  if( 0 == texture){
    std::cout<<"SOIL: Error loading image (" << name << ", " << path << "): " << SOIL_last_result() << "\n";
    texture = SOIL_load_OGL_texture
      (
       "res/defaultTexture.png",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y
       );
  }

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
}
void RegTexture::consoleDump(){
  std::cout<<"Unmapped Texture. Name: " << name << " Address: " <<this<< " Tex Address: " << texture << "\n";
  std::cout<<"===================================================\n";
}