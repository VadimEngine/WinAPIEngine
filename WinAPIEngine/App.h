#pragma once
#include "CustomWindow.h"
#include "CustomTimer.h"
#include "ImguiManager.h"
#include "Camera.h"

#include "Scene.h"

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

	Camera cam;

	//Update to vector of scenes and cycle through them with tab(Or imgui)
	Scene theScene;

public:
	App();
	~App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();
};

