#ifndef __MDSCENEMANAGER__
#define __MDSCENEMANAGER__
#include "Module.h"
#include <list>
#include "SDL\include\SDL.h"
#include "p2Point.h"
#include "Character.h"
#include "mdInput.h"
#include "Buttons.h"
#include "Bars.h"
#include "Labels.h"
#include "PerfTimer.h"

//PROVISIONAL: Nyeh, needed to do fade to black
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )


enum ui_elem_type;
enum button_types;
enum bar_types;

enum scene_type {ONE_VS_ONE, TWO_VS_TWO, MAIN_MENU, START_SCENE}; //To make a switch for specific code later

struct CharacterInfo {
	int player;
	int x_pos;
	CHAR_TYPE type;
	bool flipped;
};

struct LabelInfo {
	const char* text;
	SDL_Color color;
	_TTF_Font* font_size;
};

struct WidgetInfo {
	iPoint pos;
	bool flip;
	ui_elem_type type;
	button_types button_type; //in xml, leave empty if item is not a button
	bar_types bar_type; //in xml, leave empty if item is not a bar
	LabelInfo label_info;  //in xml, leave empty if item is not a label
};



struct Scene {
	scene_type type; 
	std::list<CharacterInfo> characters; //to create scenes with 2 or 4 characters
	std::list<WidgetInfo> ui_elements;
};



class mdSceneManager : public Module{
public:
	mdSceneManager();
	~mdSceneManager();

	bool awake(const pugi::xml_node& md_config) override;
	bool start() override;
	bool update(float dt) override;

	bool changeScene(Scene* scene_to_load);
	bool onEvent(Buttons* button);

private:
	bool createCharacters();
	bool createWidgets();
	void loadSceneUI();
	void loadSceneCharacters();
	void updateTimer();
	void blitUiTextures();


public:
	std::list<Scene> scenes;
	Scene* current_scene = nullptr;
	Scene* scene_to_load = nullptr;
	bool	paused = false;

private:
	enum fade_step
	{
		NONE,
		FADE_TO_BLACK,
		FADE_FROM_BLACK
	} current_step = fade_step::NONE;

	SDL_Rect screen;
	float fadetime = 1.0f;
	Timer switch_timer;
	//HARDCODE
	///When reading this from an XML, names should not be necesary

	Scene one_vs_one;
	Scene two_vs_two;
	Scene main_menu;
	Scene start_scene;

	CharacterInfo player1;
	CharacterInfo player2;

	CharacterInfo player3;
	CharacterInfo player4;

	//START SCENE UI
	WidgetInfo intro_label;
	SDL_Texture* game_logo = nullptr;

	//MAIN MENU UI
	WidgetInfo b_o_vs_o;
	WidgetInfo b_t_vs_t;
	WidgetInfo b_exit;

	WidgetInfo l_o_vs_o;
	WidgetInfo l_t_vs_t;
	WidgetInfo l_exit;

	//COMBAT UI
	WidgetInfo health_bar1;
	WidgetInfo health_bar2;
	WidgetInfo health_bar3;
	WidgetInfo health_bar4;
	WidgetInfo super_bar1;
	WidgetInfo super_bar2;
	WidgetInfo super_bar3;
	WidgetInfo super_bar4;
	Labels* timer;
	SDL_Rect timer_rect;
	SDL_Rect character1_rect;
	SDL_Rect character2_rect;
	SDL_Rect character3_rect;
	SDL_Rect character4_rect;
	SDL_Rect character1_image;
	SDL_Rect character2_image;
	SDL_Rect character3_image;
	SDL_Rect character4_image;

	//Combat scene timer
	uint	timer_count = 0;
	uint	current_time = 90;
	uint	max_time = 90;
	Timer	scene_timer;


};

#endif