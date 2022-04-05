#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Point.h"
#include "DynArray.h"

#include "Spline.h"
#include "EasingFunctions.h"

struct SDL_Texture;
class LevelScene;
class Player;

typedef short unsigned int suint;

enum Scenes
{
	NO_SCENE = -1,
	LOGO_SCENE,
	LEVEL_SCENE,
};

class Scene : public Module
{
public:

	Scene();

	virtual ~Scene();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	Scenes GetCurrScene() const
	{
		return currScene;
	}

private: //DEBUG

	void DebugCommands();
	bool exit = false;
	bool activeContinue = false;

private: //Pointers
	Player* player1 = nullptr;
	LevelScene* level = nullptr;

private: //SPLINES
	Spline spline;
	EasingFunctions easing;

public://Scene Manager
	void SetScene(Scenes scene);

private:
	Scenes currScene = NO_SCENE;
	Scenes prevScene = NO_SCENE;

	//Setters
	void SetLogoScene();
	void SetLevelScene();

	//Updaters
	void UpdateLogoScene(float dt);
	void UpdateLevelScene(float dt);

private: //BUTTONS
	bool OnGuiMouseClickEvent(GuiControl* control);

};

#endif // __SCENE_H__