#ifndef _skilLib
#define _skilLib

#include <stdio.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <string>

const float SKILLIB_VERSION = 0.1;

class Setting;
class IOManager;
class SettingsManager;
class Engine;
class MessageHandler;
class Message;
class Registry;

extern GLFWwindow* window;
void shutDownEverything();
void messageSystems(Message *m);

Registry* getRegistry();

std::vector<std::string> split(std::string, char);

/*
Class Animation
*/

class Animation{
	Animation(std::string getName, int getFps, int getNumFrames, std::string getPathBase);
	Animation(std::string getName, int getFps, int getNumFrames, std::string getPathBase, std::string getExtension);
	GLuint* nextFrame(double delta);
	GLuint* frameAt(int x);
	void reset();
private:
	std::string name;
	double deltaT;
	int currentFrame;
	int fps;
	int numFrames;
	std::string pathBase;
	std::string extension;
	std::vector<GLuint*> frames;
};

class Test{
 public:
  Test();
  Test(int emacs);
  bool isEmacsFun;
  bool doesSaveWork;
};
/*
Class Setting
Holds a double value and a string name.
Might need to have capability to set non-double value
*/

class Setting{
public:
	Setting();
	Setting(std::string getName);
	Setting(std::string getName, double getValue);
	std::string getName();
	double getValue();
	void setValue(double newVal);
	std::string saveValue();
private:
	std::string name;
	double value;
};

/*
Class IOManager
Handles Input/Output related tasks, particularly file operations.
KeyDown seems like it should perhaps be placed in another place, with callback based system instead of the current polling based one.
*/
class IOManager{
public:
	IOManager();
	IOManager(GLFWwindow* getwindow);
	GLFWwindow* window;
	bool keyDown(int key);
	std::string getFile(std::string filename);
	void saveFile(std::string filename, std::string contents);
	void writeFile(std::string filename, std::vector<std::string> lines);
};

/*
Class SettingsManager
Stores instances of the class Settings
Can load and save to files
Will return double value for setting when fed name value.
*/
class SettingsManager{
public:
	SettingsManager();
	SettingsManager(IOManager *getio);
	SettingsManager(IOManager *io, std::string settingFile);
	double getSetting(std::string name);
	void setSetting(std::string, double value);
	void displaySettings();
	void reloadSettings();
	void saveSettings();
protected:
	IOManager* io;
	std::vector<Setting> settings;
	std::string filename;
};

/*
Class KeybindManager
Basically a settings manager for keys.
Designed to keep keybinds and settings in separate files.
Also makes it easier to check for what key we check. Only need to poll for intended action (ie "walkLeft") to recieve bool
*/
class KeybindManager: SettingsManager{
public:
	KeybindManager();
	KeybindManager(IOManager *getio);
	KeybindManager(IOManager *getio, std::string settingFile);
	bool isDown(std::string name);
	//Scan 1-350 for keybinds
};

/*
Class Message
Base class to enable messages between components and engines.
Seemed more useful when I wrote it. Currently only seems to be used to send the Delta message?
*/

class Message{
public:
	Message();
	int fromType;
	int messageType;
};

/*
Class Component
Base component. These are critical to our system here.
Holds a bit of data, that differs based on what type of component it is.
*/

class Component{
public:
	Component();
	virtual ~Component();
	virtual Component *spawn(std::string sig, std::string args) = 0;
	/*
	virtual Component* construct() = 0;
	virtual Component* construct(std::string args) = 0;
	*/
	//virtual void update(float delta) = 0;
	int getID();
	void setID(int getid);
	int id;

};

/*
Class Entity
Similarly critical for the function of the system.
An Entity is essentially just a wrapper for components. All that the class really does is handle messages and hold components.
*/

class Entity{
public:
	Entity();
	Entity(MessageHandler *gmh);
	void message(Message* msg);
	bool addComponent(Component* comp);
	bool removeComponent(int compID);
	bool hasComponent(int compID);
	Component *getComponent(int compID);
	void update(int delta);
protected:
	MessageHandler *mh;
	std::vector<Component*> components;
};

/*
Class System
Like a component, except that it plugs into the Engine instead of an Entity, and it has functions, not data.
*/

class System{
public:
	System();
	virtual void update(float delta) = 0;
	void setIndex(int ind);
	void engineMessage(Message *m);
	void recieveMessage(Message *m);
	Entity *entityAt(int index);
	int numEntities();
	int getID();
	int id;
	int index;
	void message(Message* msg);
	MessageHandler *handler;
};

/*
Class MessagedHandler
It handles messages.
Base class, plugs into System or Entity.
*/

class MessageHandler{
public:
	MessageHandler();
	virtual void handle(Message *m, Entity *ent);
	virtual void handle(Message *m, System *sys);
};

/*
Class EntityDef
Entity definition
Can be cloned to Entity. Holds references to Animations, SFX, and components
*/

class EntityDef{
public:
	EntityDef();
	std::vector<std::string> components;
	std::vector<std::string> animations;
	std::vector<std::string> sounds;

private:
	//Collection *collection;
};


class RegComponent{
public:
	RegComponent();
	RegComponent(std::string gName, std::vector<std::string> gSignatures);
	std::string name;
	Component *seed;
	std::vector<std::string> signatures;
};

class RegTexture{
public:
	RegTexture(std::string gName);
	RegTexture(std::string gName, std::string path);
	GLuint texture;
	std::string name;

};

class RegTextureMapped{
public:
	RegTextureMapped(std::string gName, std::string gFull);
	RegTextureMapped(std::string gName, std::string gFull, float *gx, float *gy);
	GLuint getTex();
	std::string name;
	std::string source;
	float x[4];
	float y[4];
	RegTexture* tex;
};

class Registry{
public:
	Registry();
	bool Register(Component* c, std::string name);
	bool declare(std::string name, std::vector<std::string> signatures);
	bool addTextureUnmapped(std::string name, std::string path);
	bool addTextureMapped(std::string name, std::string source, float *gx, float *ogy);
	RegTexture *getTexture(std::string);
	RegTextureMapped *getTextureMapped(std::string);
	
	// Needs to have an add audio eventually
	
	Component* getComponent(std::string args);
private:
	std::vector<RegComponent> components;
	std::vector<RegTexture> unmappedTextures;
	std::vector<RegTextureMapped> mappedTextures;
};


/*
Class Engine
The core of the library.
Holds vectors of Entities and Systems. Game loop is here. Also has some auxillary features such as Settings and Keybinds
*/

class Engine{
public:
	Engine();
	void addEntity(Entity *ent);
	void removeEntity(int entIndex);
	bool addSystem(System *sys);
	bool removeSystem(int sysID);
	void recieveMessage(Message *m);
	void start();
	void update();
	void shutDown();
	Entity *getEntity(int index);
	int numEntities();
	IOManager *io;
	
	Registry registry;
protected:
	SettingsManager *settings;
	KeybindManager *keybinds;
	bool running;
	float delta;
	std::vector<Entity*> entities;
	std::vector<System*> systems;
};


#endif
