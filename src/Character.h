#ifndef __CHARACTER__
#define __CHARACTER__

#include "Animation.h"
#include "Application.h"
#include "mdInput.h"
#include "p2Point.h"
#include "mdRender.h"

enum CHAR_TYPE {
	DEF_CHAR,
	WARRIOR,
	MAGE,
	ROGUE,
	PALADIN
};

enum CHAR_ATT_TYPE {
	NO_ATT,
	CR_L,
	CR_H,
	CR_S1,
	CR_S2,
	
	ST_L,
	ST_H,
	ST_S1,
	ST_S2,

	JM_L,
	JM_H,
	JM_S1,
	JM_S2
};
enum CHAR_STATE {
	NULL_STATE,
	IDLE,
	WALKING_BACK,
	WALKING_FORWARD,
	CROUCHING,
	JUMPING,
	ATTACKING,
	SWAPPING,

	BLOCKING,
	HIT,
	JUGGLE,
	KNOCKDOWN
};

enum CHARACTER_INPUTS {
	NULL_INPUT = -1,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LIGHT_ATTACK,
	HEAVY_ATTACK,
	SPECIAL_1,
	SPECIAL_2,
	GRAB,
	SWITCH,
	MAX_INPUTS
};

class Player;

class Character {
public:
	Character();
	~Character();
						
	virtual void update(const bool (&inputs)[MAX_INPUTS]);		

	void applyGravity();

	void setIfGrounded();

	void draw(SDL_Texture* graphic) const;

	//Execute attack, rewritable for every type of character
	virtual void doAttack();					 
	//void onCollision(Collider* collider);

protected:
	void updateAnimation(Animation& new_animation);

protected:
	CHAR_TYPE type;

	iPoint position;
	iPoint velocity;

	int current_life; 								
	int max_life;	
	int walk_speed;	

	bool grounded;
	int jump_power;

	int lane = 1; //Provisional 1 = bottom  2 = top

	bool fliped;
	bool hit = false;

	// Entity collider
	//collider* hurtbox;								 
	

	//input_values assigned_inputs;
	//active_inputs inputs_pressed;
	

	CHAR_STATE current_state;
	CHAR_ATT_TYPE attack_doing;

	Animation* current_animation;
	Animation idle, walk_forward, walk_back, crouch, light_attack, heavy_attack, jump, crouching_light, crouching_heavy;

	Player* owner;


	//PROVISIONAL should be read from xml
	float gravity = 1;
	int bottom_lane = 300;
};

#endif //__CHARACTER__
