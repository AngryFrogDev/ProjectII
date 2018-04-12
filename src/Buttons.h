#ifndef _BUTTONS_
#define _BUTTONS_

#include "Widgets.h"
#include "mdGuiManager.h"

#include "SDL/include/SDL.h"

class Buttons : public Widgets {
public:
	Buttons(button_types type, button_size _size, std::pair<int, int> pos, Module* callback);
	virtual ~Buttons();

	bool preUpdate();
	
	void draw();
	void getSection(SDL_Rect idle_sec, SDL_Rect highl_sec, SDL_Rect clicked_sec, SDL_Rect disabled_sec);
	
private:
	void changeVisualState(controller_events event);
	void loadGuiFromAtlas();

public:
	bool being_clicked = false;
	bool hovering = false;
	button_types button_type = NO_BUTTON;
	button_size size = NO_SIZE;

private:
	SDL_Rect click_rect;
	SDL_Rect still_rect;
	SDL_Rect highl_rect;
	SDL_Rect disabled_rect;
	SDL_Rect* current_rect = nullptr;
	
	bool enabled = true;
	bool is_clicked = false;

	uint click_sfx;

};
#endif
