#ifndef __j1APP_H__
#define __j1APP_H__

#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "PugiXml\src\pugixml.hpp"
#include <list>

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1FileSystem;
class j1Scene;
class j1Fonts;
class j1Gui;
class j1Module;
class j1BuffOpt; 
class j1Player; 


class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	float GetDT() const;

	void LoadGame(const char* file);
	void SaveGame(const char* file) const;
	void GetSaveGames(std::list<std::string*>& list_to_fill) const;

	bool IsXMLdir(const char* dir)const;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow();

public:

	// Modules
	j1Window*			win = NULL;
	j1Input*			input = NULL;
	j1Render*			render = NULL;
	j1Textures*			tex = NULL;
	j1Scene*			scene = NULL;
	j1FileSystem*		fs = NULL;
	j1Fonts*			font = NULL;
	j1Gui*				gui = NULL;
	j1BuffOpt*       buffdebuff = NULL;
	j1Player*           player = NULL; 

	
	// Add a new module to handle
	void		AddModule(j1Module* module);
	//Get Module pointer by name
	j1Module*	GetModule(const  std::string* module_name);
	//Get number of modules
	uint		GetModulesNum()const;
	//Get module of position x in array
	j1Module*	GetModuleAt(uint index)const;

public:

	//Get config xml file
	pugi::xml_node GetConfigXML()const;

	

private:

	pugi::xml_node config_node;

	std::list<j1Module*>	modules;
	int						argc;
	char**					args;

	std::string				title;
	std::string				organization;

	mutable bool			want_to_save = false;
	bool					want_to_load = false;
	std::string				load_game;
	mutable  std::string	save_game;

	j1PerfTimer			ptimer;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float				dt = 0.0f;
	int					capped_ms = -1;

	bool				want_to_quit = false;


	mutable std::list<std::string*>	saved_games;

public:

	void SetQuit();

};

extern j1App* App;

#endif