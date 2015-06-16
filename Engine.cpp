#include <iostream>
#include <string>
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

extern Engine *theEngine;

void Engine::loadXUPL(std::string path){
	std::vector<std::string> theFile = io->getFileAsVector(path);
	
	for(int x = 0; x < theFile.size(); x++){

		// If space blank or comment, skip it
		if(theFile[x].size() < 2 || (theFile[x][0] == '/' && theFile[x][1] == '/')){
		
			// skip
		
		// Component
		}else if(theFile[x] == "component"){
		
			std::string name;
			std::vector<std::string> sigs;

			x++;
			while(x < theFile.size() && theFile[x].size() > 2){
				std::vector<std::string> params = split(theFile[x], ':');
				params[0].erase(params[0].begin());
				params[1].erase(params[1].begin());
				
				if(params[0] == "name"){
					name=params[1];
				}
				if(params[0] == "signature"){
					sigs.push_back(params[1]);
				}
				x++;

			}
			registry.declare(name, sigs);
		
		// Texture
		}else if(theFile[x] == "texture"){
			std::string name;
			std::string path;

			x++;
			while(x < theFile.size() && theFile[x].size() > 2){
				std::vector<std::string> params = split(theFile[x], ':');
				params[0].erase(params[0].begin());
				params[1].erase(params[1].begin());
				
				if(params[0] == "name"){
					name = params[1];
				}
				if(params[0] == "path"){
					path = params[1];
				}
				x++;

			}
			registry.addTextureUnmapped(name, path);

		// Mapped Texture
		}else if(theFile[x] == "textureMapped"){
			std::string name;
			std::string tex;
			float xMaps[4] = {0.0, 1.0, 1.0, 0.0};
			float yMaps[4] = {0.0, 0.0, 1.0, 1.0};

			x++;
			while(x < theFile.size() && theFile[x].size() > 2){
				std::vector<std::string> params = split(theFile[x], ':');
				params[0].erase(params[0].begin());
				params[1].erase(params[1].begin());
				
				if(params[0] == "name"){
					name = params[1];
				}
				if(params[0] == "tex"){
					tex = params[1];
				}
				if(params[0] == "xmaps"){
					std::vector<std::string> maps = split(params[1], ' ');
					for(int y = 0; y<4; y++){
						xMaps[y] = stof(maps[y]);
					}
				}
				if(params[0] == "ymaps"){
					std::vector<std::string> maps = split(params[1], ' ');
					for(int y = 0; y<4; y++){
						yMaps[y] = stof(maps[y]);
					}
				}
				x++;

			}
			registry.addTextureMapped(name, tex, xMaps, yMaps);

		}else if(theFile[x] == "tileset"){
			std::string name;
			std::string tex;
			float width;
			float height;

			x++;
			while(x < theFile.size() && theFile[x].size() > 2){
				std::vector<std::string> params = split(theFile[x], ':');
				params[0].erase(params[0].begin());
				params[1].erase(params[1].begin());
				
				if(params[0] == "name"){
					name = params[1];
				}
				if(params[0] == "tex"){
					tex = params[1];
				}
				if(params[0] == "width"){
					width = stof(params[1]);
				}
				if(params[0] == "height"){
					height = stof(params[1]);
				}

				x++;
			}

			int z = 0;
			for(float y = 0; y < height; y+= 1){
				for(float x = 0; x < width; x+=1){
					float xMaps[4] = {x/width, x/width + 1/width, x/width + 1/width, x/width};
					float yMaps[4] = {1-(y/height + 1/height), 1-(y/height + 1/height), 1-y/height, 1-y/height};
					registry.addTextureMapped(name + std::to_string(z), tex, xMaps, yMaps);
					z++;
				}
			}
		}
	}

	registry.rePoint();	
}

Engine::Engine(){
	delta = 0.0;
	io = new IOManager();
	settings = new SettingsManager(io);
	keybinds = new KeybindManager(io);
	registry = Registry();
}

Entity *Engine::getEntity(int index){
	return entities.at(index);
}

int Engine::numEntities(){
	return entities.size();
}

void Engine::addEntity(Entity *ent){
	entities.push_back(ent);
}

void Engine::removeEntity(int entIndex){
	if(entIndex < entities.size()){
		entities.erase(entities.begin()+entIndex);
	}
}

bool Engine::addSystem(System *sys){
	for(int x = 0; x < systems.size(); x++){
		if(systems.at(x)->getID() == sys->getID()){
			return false;
		}
	}

	systems.push_back(sys);
	return true;
}

bool Engine::removeSystem(int sysID){
	for(int x = 0; x < systems.size(); x++){
		if(systems.at(x)->getID() == sysID){
			systems.erase(systems.begin()+x);
			return true;
		}
	}
	return false;
}

void Engine::update(){
	for(int x = 0; x < systems.size(); x++){
		systems.at(x)->update(delta);
	}

	//Position *pos = dynamic_cast<Position*>(entities.at(90)->getComponent(COMPONENT_POSITION));
	//std::cout<<pos->getY()<<"\n";
}

void Engine::start(){
	running = true;
	while(running){
		update();
	}
}

void Engine::shutDown(){
	running = false;
}

void Engine::recieveMessage(Message *m){
	bool found = false;
	switch(m->messageType){
	case MESSAGE_DELTA:	DeltaMessage *deltaMSG = static_cast<DeltaMessage*>(m);
				delta = deltaMSG->delta;
				found = true;
				break;
	}

	if(!found){
		for(int x = 0; x < systems.size(); x++){
			systems.at(x)->message(m);
		}
	}
}

void messageSystems(Message *m){
	theEngine->recieveMessage(m);
}

void shutDownEverything(){
	theEngine->shutDown();
}
