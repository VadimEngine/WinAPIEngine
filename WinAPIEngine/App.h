#pragma once
#include "CustomWindow.h"
#include "CameraD3D.h"
#include "ImguiManager.h"
#include "Scene.h"
#include "SceneD3d.h"

#include "GDIPlusManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"


class App {
private:
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

