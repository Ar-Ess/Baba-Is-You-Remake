#include "Scene.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"

#include "LevelScene.h"
#include "MainMenuScene.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene(GuiManager* gui, Render* render, Input* input, Textures* texture, Window* window, Audio* audio) : Module()
{
	this->gui = gui;
	this->render = render;
	this->input = input;
	this->texture = texture;
	this->window = window;
	this->audio = audio;
}

Scene::~Scene()
{}

bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

bool Scene::Start()
{
	//DEBUG BOOLS
	gui->Start(this);

	//FIRST SCENE
	if (!SetScene(LOGO_SCENE)) return false;

	//CONTINUE ACTIVITY
	/*activeContinue = false;
	if (FILE* file = fopen("save_game.xml", "r"))
	{
		fclose(file);
		activeContinue = true;
	}*/

	//SPLINE
	pugi::xml_document doc;
	spline.LoadSplines(doc);

	render->scale = 1; //Qui toqui aquesta linia de codi, la 72, i m'entero, no viu un dia més :) <3

	return true;
}

bool Scene::Update(float dt)
{
	bool ret = true;

	switch (currScene)
	{
	case LOGO_SCENE:
		ret = UpdateLogoScene(dt);
		break;

	case MAIN_MENU_SCENE:
		ret = UpdateMainMenuScene(dt);
		break;

	case LEVEL_SCENE:
		ret = UpdateLevelScene(dt);
		break;
	}

	DebugCommands();

	return (!exit && ret);
}

bool Scene::CleanUp()
{
	LOG("Freeing scene");

	switch (currScene)
	{
	case LOGO_SCENE:
		break;

	case MAIN_MENU_SCENE:
		menu->CleanUp();
		delete menu;
		menu = nullptr;
		break;

	case LEVEL_SCENE:
		level->CleanUp();
		delete level;
		level = nullptr;
		break;
	}

	return true;
}

// SCENE MANAGER

bool Scene::SetScene(Scenes scene)
{
	bool ret = true;
	CleanUp();

	prevScene = currScene;
	currScene = scene;

	switch (currScene)
	{
	case LOGO_SCENE:
		ret = SetLogoScene();
		break;

	case MAIN_MENU_SCENE:
		ret = SetMainMenuScene();
		break;

	case LEVEL_SCENE:
		ret = SetLevelScene();
		break;
	}

	easing.ResetIterations();

	return ret;
}

bool Scene::SetLogoScene()
{
	return true;
}

bool Scene::SetMainMenuScene()
{
	menu = new MainMenuScene(render, input, gui);
	menu->Start();
	return true;
}

bool Scene::SetLevelScene()
{
	level = new LevelScene(render, input, texture, window->GetWindowSize(), lvl);
	return level->Start();
}

bool Scene::UpdateLogoScene(float dt)
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) ret = SetScene(Scenes::MAIN_MENU_SCENE);

	return ret;
}

bool Scene::UpdateMainMenuScene(float dt)
{
	bool ret = true;

	if (!menu->Update(dt)) return false;
	if (!menu->Draw(dt)) return false;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		lvl = 1;
		ret = SetScene(Scenes::LEVEL_SCENE);
	}

	return ret;
}

bool Scene::UpdateLevelScene(float dt)
{
	if (!level->Update(dt)) return false;
	if (!level->Draw(dt)) return false;

	return true;
}

// GUI CONTROLS

bool Scene::OnGuiMouseClickEvent(GuiControl* control, float value, bool check)
{
	switch (currScene)
	{
	case MAIN_MENU_SCENE:
		switch (control->id)
		{
			// BUTTON
		case 1: gui->ChangeFont(control->id).Prev(); break;

			// SLIDER
		case 2: audio->ChangeVolumeMusic(value); break;

			// CHECKBOX
		case 3: gui->debug = check;
		}
		break;
	}

	return true;
}

void Scene::DebugCommands()
{
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) gui->debug = !gui->debug;

	switch (currScene)
	{
	case LOGO_SCENE:
		break;
	}
}
