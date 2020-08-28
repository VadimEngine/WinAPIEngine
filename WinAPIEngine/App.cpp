#include "App.h"

#include "Box.h"
#include <memory>


//GDI
#include "Mat3.h"
#include "Calculator.h"
#include "Camera.h"

App::App()
	: wnd(640, 480, "Custom Window"), ent(300, 300, 50, 50) {

	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 80; i++)
	{
		boxes.push_back(std::make_unique<Box>(
			wnd.Gfx(), rng, adist,
			ddist, odist, rdist
			));
	}
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));

}

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
	/*
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed: " << std::setprecision(1) << std::fixed << t << "s";
	wnd.SetTitle(oss.str());
	*/

	auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& b : boxes)
	{
		b->Update(dt);
		b->Draw(wnd.Gfx());
	}
	wnd.Gfx().EndFrame();



	//LOOP
	Mouse::Event e = wnd.mouse.Read();
	//ent.update(wnd.kbd);
	//wnd.GDIGfx().drawScene(wnd.kbd);

	/*
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().DrawTestTriange(timer.Peek(), (wnd.mouse.GetPosX() / 320.0f)-1.0f, -((wnd.mouse.GetPosY() / 240.0f) - 1.0f));
	wnd.Gfx().DrawTestTriange(timer.Peek(), 0, 0);
	wnd.Gfx().EndFrame();
	*/
}