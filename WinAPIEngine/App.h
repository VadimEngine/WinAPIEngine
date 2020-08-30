#pragma once
#include "CustomWindow.h"
#include "CustomTimer.h"

#include "Entity.h"

class App {
private:
	CustomWindow wnd;
	CustomTimer timer;
	Entity ent;
public:
	App();
	~App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
};

