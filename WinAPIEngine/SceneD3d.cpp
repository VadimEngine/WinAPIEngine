#include "SceneD3d.h"


SceneD3d::Factory::Factory(Graphics& gfx)
	:gfx(gfx) {
}

std::unique_ptr<Drawable> SceneD3d::Factory::operator()() {
	switch (typedist(rng)) {
	case 0:
		return std::make_unique<Pyramid>(
			gfx, rng, adist, ddist,
			odist, rdist
			);
	case 1:
		return std::make_unique<Box>(
			gfx, rng, adist, ddist,
			odist, rdist, bdist
			);
	case 2:
		return std::make_unique<Melon>(
			gfx, rng, adist, ddist,
			odist, rdist, longdist, latdist
			);
	case 3:
		return std::make_unique<Sheet>(
			gfx, rng, adist, ddist,
			odist, rdist
			);
	case 4:
		return std::make_unique<SkinnedBox>(
			gfx, rng, adist, ddist,
			odist, rdist
			);
	default:
		assert(false && "bad drawable type in factory");
		return {};
	}
}

SceneD3d::SceneD3d(Graphics& d3d) {
	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, Factory{ d3d });

	const auto s = Surface::FromFile("Images\\kappa50.png");

	d3d.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f)); d3d.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
	d3d.SetCamera(DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f));
}


void SceneD3d::render(Graphics& d3d, Mouse& mouse, Keyboard& keyboard, CustomTimer& timer, CameraD3D& theCam) {
	const auto dt = timer.Mark() * speed_factor;

	d3d.BeginFrame(0.07f, 0.0f, 0.12f);
	d3d.SetCamera(theCam.GetMatrix());

	for (auto& d : this->drawables) {
		d->Update(keyboard.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
		d->Draw(d3d);
	}

	// imgui window to control simulation speed
	if (ImGui::Begin("Simulation Speed")) {
		ImGui::SliderFloat("Speed Factor", &speed_factor, 0.0f, 4.0f);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Status: %s", keyboard.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING");
	}

	ImGui::End();
	// imgui window to control camera
	theCam.SpawnControlWindow();
	// present
	d3d.EndFrame();
}