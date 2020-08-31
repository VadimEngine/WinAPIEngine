#pragma once
#include "CustomWindow.h"
#include "CustomTimer.h"
#include "ImguiManager.h"
#include "Camera.h"


#include "Entity.h"

class App {
private:
	ImguiManager imgui;
	CustomWindow wnd;
	CustomTimer timer;
	Entity ent;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	float speed_factor = 1.0f;
	Camera cam;
	static constexpr size_t nDrawables = 180;
public:
	App();
	~App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();
};

