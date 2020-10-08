#pragma once
#include "CustomWindow.h"
#include "CustomTimer.h"
#include "ImguiManager.h"
#include "CameraD3D.h"

#include "Scene.h"
#include "SceneD3d.h"

#include <memory>
#include <algorithm>
#include "CustomMath.h"
#include "GDIPlusManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

class App {
private:
	ImguiManager imgui;
	CustomWindow wnd;
	CustomTimer timer;

	CameraD3D cam;

	//Update to vector of scenes and cycle through them with tab(Or imgui)
	SceneD3d theSceneD3d;

	//list of graphics
	//list of scenes
	//graphics pointer
	//camera (Camera should be managed by the scene...)

	unsigned int graphicsIndex;
	unsigned int sceneIndex;

	std::vector<AbstractGraphics*> graphics;
	std::vector<Scene> scenes;
	//std::vector

	


public:
	App();
	~App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();

	void populateScenes();
};

