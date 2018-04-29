#include "Application.h"
#include "characterSelScene.h"
#include "mdGuiManager.h"



characterSelScene::characterSelScene(bool active) : scene(CHAR_SEL_SCENE)	{
	scene_active = active;

	buttons_node = scene_config.child("char_sel_scene").child("buttons");
	labels_node = scene_config.child("char_sel_scene").child("labels");
	textures_node = scene_config.child("char_sel_scene").child("textures");
	setRects();
	//By default, both player have Warrior selected
	player1.character = player2.character = WARRIOR;
}


characterSelScene::~characterSelScene()	{}

bool characterSelScene::start()	{
	character_potraits = App->textures->load(textures_node.child("portraits_tex").attribute("path").as_string());
	vs_tex = App->textures->load(textures_node.child("vs_tex").attribute("path").as_string());
	character_names = App->textures->load("assets/character_name_tex.png");
		
	loadSceneUi();
	assignFocus();
	
	return true;
}

bool characterSelScene::update(float dt)	{
	setCurrentCharDisplay();
	loadSceneTextures();
	checkSceneInput();
	App->gui->draw();

	return true;
}

bool characterSelScene::onEvent(Buttons* button)	{
	switch (button->button_type)
	{
	default:
		break;
	case SELECT_WARRIOR:
		if (button->focus_id == 0)
			player1.character = WARRIOR, player1.name_tex = &warrior_name_tex;
		else 
			player2.character = WARRIOR, player2.name_tex = &warrior_name_tex;
		break;
	case SELECT_MAGE:
		if (button->focus_id == 0)
			player1.character = MAGE, player1.name_tex = &mage_name_tex;
		else 
			player2.character = MAGE, player2.name_tex = &mage_name_tex;
		break;
	case SELECT_ROGUE:
		if (button->focus_id == 0)
			player1.character = ROGUE, player1.name_tex = &rogue_name_tex;
		else 
			player2.character = ROGUE, player2.name_tex = &rogue_name_tex;
		break;
	case SELECT_PALADIN:
		if (button->focus_id == 0)
			player1.character = PALADIN, player1.name_tex = &paladin_name_tex;
		else 
			player2.character = PALADIN, player2.name_tex = &paladin_name_tex;
		break;
	}

	if (button->being_clicked)
	{
		if (button->focus_id == 0)
			player1.has_selected_character = true;
		else
			player2.has_selected_character = true;

	//	popUpWindow();
	}

	return true;
}

void characterSelScene::loadSceneUi()	{
	//LABELS
	scene_title = (Labels*)App->gui->createLabel(labels_node.child("title").child("content").attribute("value").as_string(), { (Uint8)labels_node.child("title").child("color").attribute("r").as_int(),(Uint8)labels_node.child("title").child("color").attribute("g").as_int(),(Uint8)labels_node.child("title").child("color").attribute("b").as_int(),(Uint8)labels_node.child("title").child("color").attribute("a").as_int() },
	App->fonts->extra_large_size, { labels_node.child("title").child("pos").attribute("x").as_int(), labels_node.child("title").child("pos").attribute("y").as_int() }, this);

	p1_label = (Labels*)App->gui->createLabel(labels_node.child("player_1").child("content").attribute("value").as_string(), { (Uint8)labels_node.child("player_1").child("color").attribute("r").as_int(),(Uint8)labels_node.child("player_1").child("color").attribute("g").as_int(),(Uint8)labels_node.child("player_1").child("color").attribute("b").as_int(),(Uint8)labels_node.child("player_1").child("color").attribute("a").as_int() },
	App->fonts->large_size, { labels_node.child("player_1").child("pos").attribute("x").as_int(), labels_node.child("player_1").child("pos").attribute("y").as_int() }, this);
	
	p2_label = (Labels*)App->gui->createLabel(labels_node.child("player_2").child("content").attribute("value").as_string(), { (Uint8)labels_node.child("player_2").child("color").attribute("r").as_int(),(Uint8)labels_node.child("player_2").child("color").attribute("g").as_int(),(Uint8)labels_node.child("player_2").child("color").attribute("b").as_int(),(Uint8)labels_node.child("player_2").child("color").attribute("a").as_int() },
	App->fonts->large_size, { labels_node.child("player_2").child("pos").attribute("x").as_int(), labels_node.child("player_2").child("pos").attribute("y").as_int() }, this);

	//BUTTONS
	//Left
	b_warrior_l = (Buttons*)App->gui->createButton(SELECT_WARRIOR, CHARACTER_SELECTION, buttons_node.child("b_warrior_l").child("player_id").attribute("value").as_int(), { buttons_node.child("b_warrior_l").child("pos").attribute("x").as_int(), buttons_node.child("b_warrior_l").child("pos").attribute("y").as_int() }, this);
	b_mage_l = (Buttons*)App->gui->createButton(SELECT_MAGE, CHARACTER_SELECTION, buttons_node.child("b_mage_l").child("player_id").attribute("value").as_int(), { buttons_node.child("b_mage_l").child("pos").attribute("x").as_int(), buttons_node.child("b_mage_l").child("pos").attribute("y").as_int() }, this);
	b_rogue_l = (Buttons*)App->gui->createButton(SELECT_ROGUE, CHARACTER_SELECTION, buttons_node.child("b_rogue_l").child("player_id").attribute("value").as_int(), { buttons_node.child("b_rogue_l").child("pos").attribute("x").as_int(), buttons_node.child("b_rogue_l").child("pos").attribute("y").as_int() }, this);
	b_paladin_l = (Buttons*)App->gui->createButton(SELECT_PALADIN, CHARACTER_SELECTION, buttons_node.child("b_paladin_l").child("player_id").attribute("value").as_int(), { buttons_node.child("b_paladin_l").child("pos").attribute("x").as_int(), buttons_node.child("b_paladin_l").child("pos").attribute("y").as_int() }, this);
	//Right
	b_warrior_r = (Buttons*)App->gui->createButton(SELECT_WARRIOR, CHARACTER_SELECTION, buttons_node.child("b_warrior_r").child("player_id").attribute("value").as_int(), { buttons_node.child("b_warrior_r").child("pos").attribute("x").as_int(), buttons_node.child("b_warrior_r").child("pos").attribute("y").as_int() }, this);
	b_mage_r = (Buttons*)App->gui->createButton(SELECT_MAGE, CHARACTER_SELECTION, buttons_node.child("b_mage_r").child("player_id").attribute("value").as_int(), { buttons_node.child("b_mage_r").child("pos").attribute("x").as_int(), buttons_node.child("b_mage_r").child("pos").attribute("y").as_int() }, this);
	b_rogue_r = (Buttons*)App->gui->createButton(SELECT_ROGUE, CHARACTER_SELECTION, buttons_node.child("b_rogue_r").child("player_id").attribute("value").as_int(), { buttons_node.child("b_rogue_r").child("pos").attribute("x").as_int(), buttons_node.child("b_rogue_r").child("pos").attribute("y").as_int() }, this);
	b_paladin_r = (Buttons*)App->gui->createButton(SELECT_PALADIN, CHARACTER_SELECTION, buttons_node.child("b_paladin_r").child("player_id").attribute("value").as_int(), { buttons_node.child("b_paladin_r").child("pos").attribute("x").as_int(), buttons_node.child("b_paladin_r").child("pos").attribute("y").as_int() }, this);
}

void characterSelScene::loadSceneTextures()	{

	//Player 1 portrait (left)
	if (player1.portrait == &paladin_portrait || player1.portrait == &warrior_portrait)
		App->render->drawSprite(3, character_potraits, textures_node.child("left_portraits").attribute("x").as_int(), textures_node.child("left_portraits").attribute("y").as_int(), player1.portrait, textures_node.child("portraits").attribute("scale").as_int(), true, 1.0f, 0, 0, 0, false);
	else
		App->render->drawSprite(3, character_potraits, textures_node.child("left_portraits").attribute("x").as_int(), textures_node.child("left_portraits").attribute("y").as_int(), player1.portrait, textures_node.child("portraits").attribute("scale").as_int(), false, 1.0f, 0, 0, 0, false);

	//Player 2 portrait (right)
	if (player2.portrait == &rogue_portrait || player2.portrait == &mage_portrait)
		App->render->drawSprite(3, character_potraits, textures_node.child("right_portraits").attribute("x").as_int(), textures_node.child("right_portraits").attribute("y").as_int(), player2.portrait, textures_node.child("portraits").attribute("scale").as_int(), true, 1.0f, 0, 0, 0, false);
	else
		App->render->drawSprite(3, character_potraits, textures_node.child("right_portraits").attribute("x").as_int(), textures_node.child("right_portraits").attribute("y").as_int(), player2.portrait, textures_node.child("portraits").attribute("scale").as_int(), false, 1.0f, 0, 0, 0, false);

	//VS
	App->render->drawSprite(4, vs_tex, textures_node.child("vs_tex").attribute("x").as_int(), textures_node.child("vs_tex").attribute("y").as_int(), 0, textures_node.child("vs_tex").attribute("scale").as_int(), false, 1.0f, 0, 0, 0, false);

	//CHARACTER MINIATURES
	//Left
	App->render->drawSprite(3, App->gui->atlas, 686, 306, &warrior_miniature, 3, false, 1.0f, 0, 0, 0, false);
	App->render->drawSprite(3, App->gui->atlas, 686, 456, &mage_miniature, 3, false, 1.0f, 0, 0, 0, false);
	App->render->drawSprite(3, App->gui->atlas, 686, 606, &rogue_miniature, 3, false, 1.0f, 0, 0, 0, false);
	App->render->drawSprite(3, App->gui->atlas, 686, 756, &paladin_miniature, 3, false, 1.0f, 0, 0, 0, false);

	//Right
	App->render->drawSprite(3, App->gui->atlas, 1056, 306, &warrior_miniature, 3, false, 1.0f, 0, 0, 0, false);
	App->render->drawSprite(3, App->gui->atlas, 1056, 456, &mage_miniature, 3, false, 1.0f, 0, 0, 0, false);
	App->render->drawSprite(3, App->gui->atlas, 1056, 606, &rogue_miniature, 3, false, 1.0f, 0, 0, 0, false);
	App->render->drawSprite(3, App->gui->atlas, 1056, 756, &paladin_miniature, 3, false, 1.0f, 0, 0, 0, false);

	//CHARACTER NAME TEXTURES
	//Left
	App->render->drawSprite(4, character_names, textures_node.child("left_names").attribute("x").as_int(), textures_node.child("left_names").attribute("y").as_int(), player1.name_tex, textures_node.child("names").attribute("scale").as_int(), false, 1.0f, 0, 0, 0, false);
	//Right
	App->render->drawSprite(4, character_names, textures_node.child("right_names").attribute("x").as_int(), textures_node.child("right_names").attribute("y").as_int(), player2.name_tex, textures_node.child("names").attribute("scale").as_int(), false, 1.0f, 0, 0, 0, false);

}

void characterSelScene::assignFocus()	{
	if (!App->gui->p1_focus_elements.empty() && !App->gui->p2_focus_elements.empty())
	{
		App->entities->players[0]->focus = *App->gui->p1_focus_elements.begin();
		App->entities->players[1]->focus = *App->gui->p2_focus_elements.begin();
	}
}

void characterSelScene::checkSceneInput()	{
	//Check player 1 input and player 2 input to select characters and objects

}

void characterSelScene::assignCharacterToPlayer()	{

}

void characterSelScene::setRects()	{
	//PORTRAITS
	pugi::xml_node warrior = textures_node.child("warrior_portrait");
	pugi::xml_node mage = textures_node.child("mage_portrait");
	pugi::xml_node rogue = textures_node.child("rogue_portrait");
	pugi::xml_node paladin = textures_node.child("paladin_portrait");

	warrior_portrait.x = warrior.attribute("x").as_int();
	warrior_portrait.y = warrior.attribute("y").as_int();
	warrior_portrait.w = warrior.attribute("w").as_int();
	warrior_portrait.h = warrior.attribute("h").as_int();

	mage_portrait.x = mage.attribute("x").as_int();
	mage_portrait.y = mage.attribute("y").as_int();
	mage_portrait.w = mage.attribute("w").as_int();
	mage_portrait.h = mage.attribute("h").as_int();

	rogue_portrait.x = rogue.attribute("x").as_int();
	rogue_portrait.y = rogue.attribute("y").as_int();
	rogue_portrait.w = rogue.attribute("w").as_int();
	rogue_portrait.h = rogue.attribute("h").as_int();

	paladin_portrait.x = paladin.attribute("x").as_int();
	paladin_portrait.y = paladin.attribute("y").as_int();
	paladin_portrait.w = paladin.attribute("w").as_int();
	paladin_portrait.h = paladin.attribute("h").as_int();

	//MINIATURES
	warrior = textures_node.child("warrior_miniature");
	mage = textures_node.child("mage_miniature");
	rogue = textures_node.child("rogue_miniature");
	paladin = textures_node.child("paladin_miniature");

	warrior_miniature.x = warrior.attribute("x").as_int();
	warrior_miniature.y = warrior.attribute("y").as_int();
	warrior_miniature.w = warrior.attribute("w").as_int();
	warrior_miniature.h = warrior.attribute("h").as_int();

	mage_miniature.x = mage.attribute("x").as_int();
	mage_miniature.y = mage.attribute("y").as_int();
	mage_miniature.w = mage.attribute("w").as_int();
	mage_miniature.h = mage.attribute("h").as_int();

	rogue_miniature.x = rogue.attribute("x").as_int();
	rogue_miniature.y = rogue.attribute("y").as_int();
	rogue_miniature.w = rogue.attribute("w").as_int();
	rogue_miniature.h = rogue.attribute("h").as_int();

	paladin_miniature.x = paladin.attribute("x").as_int();
	paladin_miniature.y = paladin.attribute("y").as_int();
	paladin_miniature.w = paladin.attribute("w").as_int();
	paladin_miniature.h = paladin.attribute("h").as_int();

	//NAME TEXTURES
	warrior = textures_node.child("warrior_name");
	mage = textures_node.child("mage_name");
	rogue = textures_node.child("rogue_name");
	paladin = textures_node.child("paladin_name");

	warrior_name_tex.x = warrior.attribute("x").as_int();
	warrior_name_tex.y = warrior.attribute("y").as_int();
	warrior_name_tex.w = warrior.attribute("w").as_int();
	warrior_name_tex.h = warrior.attribute("h").as_int();

	mage_name_tex.x = mage.attribute("x").as_int();
	mage_name_tex.y = mage.attribute("y").as_int();
	mage_name_tex.w = mage.attribute("w").as_int();
	mage_name_tex.h = mage.attribute("h").as_int();

	rogue_name_tex.x = rogue.attribute("x").as_int();
	rogue_name_tex.y = rogue.attribute("y").as_int();
	rogue_name_tex.w = rogue.attribute("w").as_int();
	rogue_name_tex.h = rogue.attribute("h").as_int();

	paladin_name_tex.x = paladin.attribute("x").as_int();
	paladin_name_tex.y = paladin.attribute("y").as_int();
	paladin_name_tex.w = paladin.attribute("w").as_int();
	paladin_name_tex.h = paladin.attribute("h").as_int();
}

void characterSelScene::setCurrentCharDisplay()	{
	//Function to set all current character's info to screen

	switch (player1.character)
	{
	default:
		break;
	case WARRIOR:
		player1.portrait = &warrior_portrait;
		player1.name_tex = &warrior_name_tex;
		break;
	case MAGE:
		player1.portrait = &mage_portrait;
		player1.name_tex = &mage_name_tex;
		break;
	case ROGUE:
		player1.portrait = &rogue_portrait;
		player1.name_tex = &rogue_name_tex;
		break;
	case PALADIN:
		player1.portrait = &paladin_portrait;
		player1.name_tex = &paladin_name_tex;
		break;
	}

	switch (player2.character)
	{
	default:
		break;
	case WARRIOR:
		player2.portrait = &warrior_portrait;
		player2.name_tex = &warrior_name_tex;
		break;
	case MAGE:
		player2.portrait = &mage_portrait;
		player2.name_tex = &mage_name_tex;
		break;
	case ROGUE:
		player2.portrait = &rogue_portrait;
		player2.name_tex = &rogue_name_tex;
		break;
	case PALADIN:
		player2.portrait = &paladin_portrait;
		player2.name_tex = &paladin_name_tex;
		break;
	}
}

void characterSelScene::popUpWindow()	{

	if (!object_win_p1 && player1.has_selected_character)
	{
		object_win_p1 = (UiWindow*)App->gui->createWindow(OBJ_SELECTION, { 300, 500 }, this);
	}

	if (!object_win_p2 && player2.has_selected_character)
	{
		object_win_p2 = (UiWindow*)App->gui->createWindow(OBJ_SELECTION, { 700, 500 }, this);
	}
}

void characterSelScene::closeWindow()	{
}
