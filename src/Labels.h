#ifndef _LABELS_
#define _LABELS_

#include "Widgets.h"
#include "mdFonts.h"

#include "SDL/include/SDL.h"

class Labels : public Widgets {
public:
	Labels(const char* content, const SDL_Color& color, _TTF_Font* font_size, std::pair<int, int> pos, scene* callback);
	~Labels();

	void draw();
	void setText(const char* content, const SDL_Color &color, _TTF_Font* font_size); 
	void setArea(std::pair<int, int> area);
	void changeContent(const char* new_content, const SDL_Color &new_color);

public:
	SDL_Texture* text_texture;
	SDL_Color color;
	_TTF_Font* font_size;
};

#endif

