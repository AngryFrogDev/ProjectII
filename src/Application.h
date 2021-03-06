#ifndef __APPLICATION__
#define __APPLICATION__

#include <list>
#include "Module.h"
#include "ProjDefs.h"
#include "Timer.h"
#include "pugixml\pugixml.hpp"

class PerfTimer;
// Modules
class mdWindow;
class mdFilesystem;
class mdInput;
class mdRender;
class mdTextures;

class mdCollision;

class mdEntities;
class mdAudio;
class mdFonts;
class mdGuiManager;
class mdMap;
class mdProjectiles;
class mdSceneManager;
class mdParticleSystem;


class Application
{
public:

	// Constructor
	Application(int argc, char* args[]);

	// Destructor
	virtual ~Application();

	// Called before render is available
	bool awake();

	bool start();

	// Called each loop iteration
	bool update();

	bool finishUpdate();

	// Called before quitting
	bool cleanUp();

	// Add a new module to handle
	void addModule(Module* module);

	pugi::xml_node loadConfig(const char* file_name, pugi::xml_document& config_file);
	void delayFrame(int delay);

private:
	std::list<Module*>	modules;

	uint64				frame_count = 0;
	Timer				startup_time;
	Timer				frame_time;
	float				dt = 0.0f;
	uint				maxfps = 60;
	int                 frame_delay = 0;
	bool				delayed_frame = false;

	Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;

public:
	// Modules
	mdWindow*		window;
	mdFilesystem*	filesystem;
	mdRender*		render;
	mdInput*		input;
	mdTextures*		textures;
	mdCollision*    collision;
	mdEntities*     entities;
	mdAudio*		audio;
	mdFonts*		fonts;
	mdGuiManager*	gui;
	mdMap*			map;
	mdProjectiles*  projectiles;
	mdSceneManager*	scene_manager;
	mdParticleSystem* particle_system;

};

extern Application* App;

#endif //__APPLICATION__