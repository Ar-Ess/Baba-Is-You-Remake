#define _CRT_SECURE_NO_WARNINGS

#include "App.h"
#include "Scene.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"

#include "LevelScene.h"
#include "GuiManager.h"

#include "Defs.h"
#include "Log.h"

#include "SDL/include/SDL.h"

Scene::Scene() : Module()
{
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
	level = new LevelScene(app->render, app->input, app->win->GetWindowSize());

	//DEBUG BOOLS
	app->guiManager->debugGui = false;

	//FIRST SCENE
	SetScene(LOGO_SCENE);

	//CONTINUE ACTIVITY
	activeContinue = false;
	if (FILE* file = fopen("save_game.xml", "r"))
	{
		fclose(file);
		activeContinue = true;
	}

	//SPLINE
	pugi::xml_document doc;
	spline.LoadSplines(doc);

	app->render->scale = 1; //Qui toqui aquesta linia de codi, la 72, i m'entero, no viu un dia més :) <3

	return true;
}

bool Scene::PreUpdate()
{
	return true;
}

bool Scene::Update(float dt)
{
	switch (currScene)
	{
	case LOGO_SCENE:
		UpdateLogoScene(dt);
		break;

	case LEVEL_SCENE:
		UpdateLevelScene(dt);
		break;
	}

	return true;
}

bool Scene::PostUpdate()
{
	DebugCommands();

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		app->guiManager->debugGui = !app->guiManager->debugGui;
	}

	return !exit;
}

bool Scene::CleanUp()
{
	LOG("Freeing scene");

	switch (currScene)
	{
	case LOGO_SCENE:
		break;

	case LEVEL_SCENE:
		level->CleanUp();
		break;
	}

	return true;
}

// SCENE MANAGER

void Scene::SetScene(Scenes scene)
{
	CleanUp();

	prevScene = currScene;
	currScene = scene;

	switch (currScene)
	{
	case LOGO_SCENE:
		SetLogoScene();
		break;

	case LEVEL_SCENE:
		SetLevelScene();
		break;
	}

	easing.ResetIterations();
}

void Scene::SetLogoScene()
{	
}

void Scene::UpdateLogoScene(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) SetScene(Scenes::LEVEL_SCENE);
}

void Scene::SetLevelScene()
{
	level->Start(0);
}

void Scene::UpdateLevelScene(float dt)
{
	level->Update(dt);
	level->Draw(dt);
}

// GUI CONTROLS

bool Scene::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (currScene)
	{
	case LOGO_SCENE:
		break;
	}

	return true;
}

void Scene::DebugCommands()
{
	switch (currScene)
	{
	case LOGO_SCENE:
		break;
	}
}
