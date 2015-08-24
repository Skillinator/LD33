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
#include <math.h>
#include "ld33.h"

extern Engine *theEngine;

WinLossSystemHandler::WinLossSystemHandler(){
	// Nothing doing
}


void WinLossSystemHandler::handle(Message *m, Entity *ent){
	
	// Nothing doing here lol
}

void WinLossSystemHandler::handle(Message *m, System *sys){
	WinLossSystem *wl = static_cast<WinLossSystem*>(sys);
	if(m->messageType == MESSAGE_STRING){
		StringMessage *sm = static_cast<StringMessage*>(m);
		
		if(sm->message == "WINPROGRESS")
			wl->winprogress++;

		if(sm->message == "notoriety+")
			wl->notoriety++;
		if(sm->message == "notoriety-")
			wl->notoriety--;
	}
}