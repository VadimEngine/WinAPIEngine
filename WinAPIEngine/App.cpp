#include "App.h"

GDIPlusManager gdipm;


App::App()
	: wnd(640, 480, "Custom Window"), theScene(wnd.GDIGfx(), wnd.Gfx()){}

App::~App(){}

int App::Go() {
	while (true) {
		if (const auto ecode = CustomWindow::ProcessMessages()) {
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame() {
	//LOOP
	Mouse::Event e = wnd.mouse.Read();

	theScene.drawScene(Scene::GRAPHIC_TYPE::OPENGL, wnd.GDIGfx(), wnd.Gfx(), wnd.GOpenGL(),
		wnd.mouse, wnd.kbd, timer, cam);
}