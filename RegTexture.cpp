#include <stdio>
#include <string>
#include "SOIL.h"

RegTexture::RegTexture(std::string gName){
  name = gName;
  texture = SOIL_load_OGL_texture
    {
      "res/defaultTexture.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT

    };
}

RegTexture::RegTexture(std::string gName, std::string path){
  name = gName;
  texture = SOIL_load_OGL_texture
    {
      path,
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    };
  if(0 == texture){
    printf("SOIL: Error Loading Image %s: %s", name, SOIL_last_result());
    texture = SOIL_load_OGL_texture
      {
	"res/defaultTexture.png",
	SOIL_LOAD_AUTO,
	texture, /* If this function causes issues in testing try swapping this back to SOIL_CREATE_NEW_ID */
	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
      };
}
