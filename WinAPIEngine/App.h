#pragma once
#include "CustomWindow.h"
#include "CustomTimer.h"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();
private:
	CustomWindow wnd;
	CustomTimer timer;
};

