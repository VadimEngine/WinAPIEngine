#pragma once
#include "CustomWindow.h"
#include "CameraD3D.h"
#include "ImguiManager.h"
#include "Scene.h"
#include "SceneD3d.h"

class App {
private:
	//initializes imgui
	ImguiManager imgui;
	CustomWindow wnd;
	CustomTimer timer;

	//used for theSceneD3d
	CameraD3D cam;

	SceneD3d theSceneD3d;

	unsigned int graphicsIndex;
	unsigned int sceneIndex;

	std::vector<AbstractGraphics*> graphics;
	std::vector<Scene> scenes;
	
public:
	App();
	~App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();

	void populateScenes();
};

