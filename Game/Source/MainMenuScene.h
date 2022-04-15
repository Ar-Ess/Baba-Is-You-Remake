#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "Point.h"
#include "Render.h"
#include "Input.h"
#include "Textures.h"
#include "Scene.h"
#include "Defs.h"

class MainMenuScene
{
public: // Methods

	MainMenuScene(Render* render, Input* input, GuiManager* gui);

	~MainMenuScene();

	bool Start();

	bool Update(float dt);

	bool Draw(float dt);

	bool CleanUp();

private: // Methods

	bool DebugDraw();

private: // Variables

	Render* render = nullptr;
	Input* input = nullptr;
	GuiManager* gui = nullptr;
};

#endif // __MAIN_MENU_SCENE_H__
