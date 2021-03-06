#include "Application.h"
#include "startScene.h"
#include "mdGuiManager.h"
#include "mdRender.h"
#include "mdSceneManager.h"
#include "mdFonts.h"


startScene::startScene(bool active) : scene(START_SCENE)	{
	scene_active = active;
	name = "Start Scene";
	//Preparing nodes to ease XML reading
	labels_node = scene_config.child("start_scene").child("labels");
	textures_node = scene_config.child("start_scene").child("textures");
}


startScene::~startScene()
{
}

bool startScene::start()	{
	//PROVISIONAL: Should find another way to load all scene music
	if (!loaded)
		scene_music = App->audio->loadMusic("SFX/scene music/BGM_1.ogg"), loaded = true;

	App->audio->playMusic(scene_music);
	
	loadSceneUi();
	
	return true;
}

bool startScene::update(float dt)	{
	checkSceneInput();
	loadSceneTextures();
	App->gui->draw();

	return true;
}

void startScene::loadSceneUi()	{
	//TEXTURES 
	game_logo = App->textures->load(textures_node.child("game_logo").attribute("path").as_string());
	//LABELS
	intro_label = (Labels*)App->gui->createLabel(labels_node.child("content").attribute("value").as_string(), { (Uint8)labels_node.child("color").attribute("r").as_int(),(Uint8)labels_node.child("color").attribute("g").as_int(),(Uint8)labels_node.child("color").attribute("b").as_int(),(Uint8)labels_node.child("color").attribute("a").as_int() },
	App->fonts->large_size, { labels_node.child("pos").attribute("x").as_int(),labels_node.child("pos").attribute("y").as_int() }, this);
}

void startScene::loadSceneTextures()	{
	App->render->drawSprite(1, game_logo, 150, 150, 0, 1, false, 0, 0, 0, 0, false);
}

void startScene::checkSceneInput()	{
	if (App->input->getKey(SDL_SCANCODE_RETURN) == KEY_DOWN || App->entities->players[0]->getInput(HEAVY_ATTACK, KEY_DOWN))
		App->scene_manager->changeScene(App->scene_manager->main_scene, this);
}
