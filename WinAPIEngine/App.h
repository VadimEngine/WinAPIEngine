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

	SceneD3d* theSceneD3d;

	GraphicsGDI gCustom;
	GraphicsOpenGL gOpenGL;
	GraphicsD3D GD3d;
	 
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