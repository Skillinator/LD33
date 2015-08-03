#include <stdio.h>
#include <iostream>
#include <string>
#include "skilLib.h"

RegTextureMapped::RegTextureMapped(std::string gName, std::string gFull){
  tex = getRegistry()->getTexture(gFull);
  name = gName;
  source = gFull;
  float tmpx[4] = {0.0, 1.0, 1.0, 0.0};
  float tmpy[4] = {0.0, 0.0, 1.0, 1.0};
  for(int z = 0; z < 4; z++){
    x[z] = tmpx[z];
    y[z] = tmpy[z];
  }
}

RegTextureMapped::RegTextureMapped(std::string gName, std::string gFull, float *gx, float *gy){
  tex = getRegistry()->getTexture(gFull);
  name = gName.c_str();
  source = gFull.c_str();
  for(int z = 0; z<4; z++){
    x[z] = gx[z];
    y[z] = gy[z];
  }
}

GLuint RegTextureMapped::getTex(){
  return tex->texture;
}

void RegTextureMapped::consoleDump(){
  std::cout<<"Mapped Texture. Name: " << name << " Address: " <<this<< " Source: " << source << "\n";
  std::cout<<"Points: (" << x[0] <<", "<<y[0]<<")("<< x[1] <<", "<<y[1]<<")("<< x[2] <<", "<<y[2]<<")("<< x[3] <<", "<<y[3]<<")\n";
  std::cout<<"===================================================\n";
}

void RegTextureMapped::rePoint(){
  tex = getRegistry()->getTexture(source);
}