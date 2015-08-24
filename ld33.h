#ifndef _LD33
#define _LD33

#include <vector>
#include <string>
#include "skilLib.h"
#include "systems.h"
#include "components.h"
#include "messages.h"

const int LD33_ISUFOCOMPONENT = 100;
const int LD33_UFOFLYINGCOMPONENT = 101;
const int LD33_UFOBEAMINGCOMPONENT = 102;
const int LD33_UFOBEAMEFFECTCOMPONENT = 103;
const int LD33_UFOENGINEEFFECTCOMPONENT = 104;
const int LD33_ABDUCTIBLECOMPONENT = 105;

const int LD33_BRAINWASHABLECOMPONENT = 106;
const int LD33_BRAINWASHEDCOMPONENT = 107;
const int LD33_RELEASABLECOMPONENT = 108;
const int LD33_EMPLOYABLECOMPONENT = 109;
const int LD33_EMPLOYEDCOMPONENT = 110;

const int LD33_WINPROGRESS = 111;

const int LD33_PLACEONE = 112;
const int LD33_PLACETWO = 113;
const int LD33_PLACETHREE = 114;
const int LD33_PLACEFOUR = 115;
const int LD33_PLACEFIVE = 112;

const int LD33_ISENGINEER = 113;
const int LD33_ISDJ = 114;
const int LD33_ISMECHANIC = 115;


const int LD33_UFOCONTROLSYSTEM = 101;
const int LD33_UFOPARTICLESYSTEM = 102;
const int LD33_ABDUCTIONSYSTEM = 103;
const int LD33_WINLOSSSYSTEM = 104;
const int LD33_CORRUPTIONSYSTEM = 105;

class UFOControlSystem : public System{
public:
	UFOControlSystem();
	void update(float delta);
	float UFOBob;
};

class UFOParticleSystem : public System{
public:
	UFOParticleSystem();
	void update(float delta);
	float ufox;
	float ufoy;
	bool toggleBeam;
	bool toggleEngine;
	bool beamActive;
	bool engineActive;
};

class AbductionSystem : public System{
public:
	AbductionSystem();
	void update(float delta);
	float ufox;
	float ufoy;
	bool beam;
	Entity* currentAbductee;
	float progress;

	bool slot1;
	bool slot2;
	bool slot3;
	bool slot4;
	bool slot5;
};

class WinLossSystem : public System{
public:
	WinLossSystem();
	void update(float h);

	int winprogress;
	float notoriety;
};

class WinLossSystemHandler : public MessageHandler{
public:
	WinLossSystemHandler();
	void handle(Message*, Entity*);
	void handle(Message*, System*);
};



#endif