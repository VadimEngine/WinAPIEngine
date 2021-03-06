#include "App.h"

App::App()
	: wnd(640, 480, "Custom Window"), theSceneD3d(wnd.Gfx()){

	graphics.push_back(&wnd.GDIGfx());	// custom
	graphics.push_back(&wnd.GOpenGL());	// openGL
	graphics.push_back(&wnd.Gfx());		// direct 3d

	graphicsIndex = 0;

	//Populate Scene with meshes
	populateScenes();
	sceneIndex = 0;
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
	//LOOP
	Mouse::Event e = wnd.mouse.Read();

	if (e.LeftIsPressed()) {
		graphicsIndex = (graphicsIndex + 1) % graphics.size();
	}

	if (e.RightIsPressed()) {
		sceneIndex = (sceneIndex + 1) % scenes.size();
	}
	// update
	scenes[sceneIndex].update(1.0f, wnd.mouse, wnd.kbd);
	// draw
	scenes[sceneIndex].render(graphics[graphicsIndex], wnd.mouse, wnd.kbd);

	//scenes[sceneIndex].drawDirect3D(&wnd.Gfx(), wnd.mouse, wnd.kbd);

	//theScene.render(&wnd.GOpenGL(), wnd.mouse, wnd.kbd);

	//theSceneD3d.render(wnd.Gfx(), wnd.mouse, wnd.kbd, timer, cam);

	/*
	theScene.drawScene(Scene::GRAPHIC_TYPE::OPENGL, wnd.GDIGfx(), wnd.Gfx(), wnd.GOpenGL(),
		wnd.mouse, wnd.kbd, timer, cam);
	*/
}

void App::populateScenes() {
	Scene scene1;

	const float height = .5f;
	const float width = .5f;

	bool flag = true;
	for (unsigned int i = 0; i < 4; i++) {// Lags at 50x50
		for (unsigned int j = 0; j < 4; j++) {
			float x = i * height;
			float y = j * width;
			float z = 0;
			if (flag) {
				scene1.addMesh(RenderableMesh({ glm::vec3(x, y, z),
										glm::vec3(x + width, y, z),
										glm::vec3(x + width, y + height, z),
										glm::vec3(x, y + height, z) },
					{ 0, 1, 2, 0 ,2, 3 }, 0x606060));
			}
			else {
				scene1.addMesh(RenderableMesh({ glm::vec3(x, y, z),
										glm::vec3(x + width, y, z),
										glm::vec3(x + width, y + height, z),
										glm::vec3(x, y + height, z) },
					{ 0, 1, 2, 0 ,2, 3 }, 0x303030));
			}
			flag = !flag;
		}
		flag = !flag;
	}

	scene1.addMesh(RenderableMesh("Images\\ExportableFox.obj", 0xFF0000));

	scenes.push_back(scene1);
	Scene scene2;
	//Scene 2
	for (unsigned int i = 0; i < 8; i++) {// Lags at 50x50
		for (unsigned int j = 0; j < 8; j++) {
			float x = i * height;
			float y = j * width;
			float z = 0;
			if (flag) {
				//float randColor = static_cast <float> (rand()) / static_cast <float> (0xFFFFFF);
				scene2.addMesh(RenderableMesh({ glm::vec3(x, y, z),
										glm::vec3(x + width, y, z),
										glm::vec3(x + width, y + height, z),
										glm::vec3(x, y + height, z) },
					{ 0, 1, 2, 0 ,2, 3 }, rand()));

			} else {
				//float randColor = static_cast <float> (rand()) / static_cast <float> (0xFFFFFF);
				scene2.addMesh(RenderableMesh({ glm::vec3(x, y, z),
										glm::vec3(x + width, y, z),
										glm::vec3(x + width, y + height, z),
										glm::vec3(x, y + height, z) },
					{ 0, 1, 2, 0 ,2, 3 }, rand()));
			}
			flag = !flag;
		}
		flag = !flag;
	}
	//int randColor = rand();
	scene2.addMesh(RenderableMesh("Images\\ExportableFox.obj", rand()));

	scenes.push_back(scene2);
}