#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

#include "Spline.h"
#include "EasingFunctions.h"

class LevelScene;
class MainMenuScene;
class GuiControl;

enum Scenes
{
	NO_SCENE = -1,
	LOGO_SCENE,
	MAIN_MENU_SCENE,
	LEVEL_SCENE,
};

class Scene : public Module
{
public:

	Scene(GuiManager* gui, Render* render, Input* input, Textures* texture, Window* window);

	virtual ~Scene();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

// SCENE MANAGER

	Scenes GetCurrScene() const
	{
		return currScene;
	}

	bool SetScene(Scenes scene);

private:
	Scenes currScene = NO_SCENE;
	Scenes prevScene = NO_SCENE;

	//Setters
	bool SetLogoScene();
	bool SetMainMenuScene();
	bool SetLevelScene();

	//Updaters
	bool UpdateLogoScene(float dt);
	bool UpdateMainMenuScene(float dt);
	bool UpdateLevelScene(float dt);

private: // Methods

	void DebugCommands();

private: // Variables

	GuiManager* gui = nullptr;
	Render* render = nullptr;
	Input* input = nullptr;
	Textures* texture = nullptr;
	Window* window = nullptr;

	bool exit = false;
	bool activeContinue = false;

	suint lvl = 0;

	MainMenuScene* menu = nullptr;
	LevelScene* level = nullptr;

	Spline spline;
	EasingFunctions easing;

};

#endif // __SCENE_H__