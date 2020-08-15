#include "App.h"

App::App()
	:
	wnd(640, 480, "Custom Window")
{}

int App::Go()
{
	while (true) {
		if (const auto ecode = CustomWindow::ProcessMessages()) {
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}

}

void App::DoFrame() {
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	wnd.SetTitle(oss.str());

	//LOOP

	Mouse::Event e = wnd.mouse.Read();

	if (wnd.kbd.KeyIsPressed(VK_MENU)) {
		MessageBox(nullptr, "Something Happened!", "Space Key Was Pressed", MB_OK | MB_ICONEXCLAMATION);
	}

	if (wnd.mouse.LeftIsPressed()) {
		std::ostringstream oss;

		oss << "(" << wnd.mouse.GetPosX() << ", " << wnd.mouse.GetPosY() << ")" << std::endl;

		OutputDebugString(oss.str().c_str());
	}

	if (e.GetType() == Mouse::Event::Type::Move) {
		std::ostringstream oss;

		oss << "(" << wnd.mouse.GetPosX() << ", " << wnd.mouse.GetPosY() << ")" << std::endl;

		OutputDebugString(oss.str().c_str());
	}



	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().EndFrame();

}