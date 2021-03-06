#ifndef _UIWINDOW_
#define _UIWINDOW_

#include "Widgets.h"
#include "SDL/include/SDL.h"

class UiWindow : public Widgets	{
public:
	UiWindow(window_type _type, std::pair<int, int> pos, scene* callback);
	virtual ~UiWindow();

	void draw();

private:
	SDL_Rect window_rect;
};

#endif

