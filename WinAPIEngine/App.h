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
	// master frame / message loop
	int Go();
private:
	void DoFrame();
};

