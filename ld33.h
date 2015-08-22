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

const int LD33_UFOCONTROLSYSTEM = 101;
const int LD33_UFOPARTICLESYSTEM = 102;

class UFOControlSystem : public System{
public:
	UFOControlSystem();
	void update(float delta);
};

class UFOParticleSystem : public System{
public:
	UFOParticleSystem();
	void update(float delta);
};

#endif