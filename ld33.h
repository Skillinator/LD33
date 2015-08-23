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

const int LD33_UFOCONTROLSYSTEM = 101;
const int LD33_UFOPARTICLESYSTEM = 102;
const int LD33_ABDUCTIONSYSTEM = 103;

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

#endif