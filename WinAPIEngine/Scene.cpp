#include "Scene.h"




Scene::Factory::Factory(Graphics& gfx)
	:gfx(gfx) { 
}

std::unique_ptr<Drawable> Scene::Factory::operator()() {
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

Scene::Scene(GraphicsGDI& gdi, Graphics& d3d)
	: ent(300, 300, 50, 50), temp("Images\\ExportableFox.obj", 0xFF0000, 100.0f)
	, cam(Vec3(640 / 2, 480 / 2, -100), Vec3(0, 0, 0)), tempSmall("Images\\ExportableFox.obj") {

	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, Factory{ d3d });

	const auto s = Surface::FromFile("Images\\kappa50.png");

	d3d.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f)); d3d.SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
	d3d.SetCamera(DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f));

	setUpScene();
}

void Scene::drawScene(GRAPHIC_TYPE graphicType, GraphicsGDI& gdi, Graphics& d3d,
	GraphicsOpenGL& gOpengl, Mouse& mouse, Keyboard& keyboard, CustomTimer& timer, Camera& theCam) {

	switch (graphicType) {
		case Scene::GRAPHIC_TYPE::DIRECT3D: {

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
				ImGui::Text("Status: %s",keyboard.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING");
			}

			ImGui::End();
			// imgui window to control camera
			theCam.SpawnControlWindow();
			// present
			d3d.EndFrame();

			break;
		}
		case Scene::GRAPHIC_TYPE::CUSTOM: {
			ent.update(keyboard);
			//gdi.drawScene(keyboard);

			float dTheta = 1;
			const float dt = 1.0f / 60.0f;

			if (keyboard.KeyIsPressed('W')) {
				cam.moveForward();
			}
			if (keyboard.KeyIsPressed('A')) {
				cam.pos.x -= dTheta;
			}
			if (keyboard.KeyIsPressed('S')) {
				cam.moveBack();
			}
			if (keyboard.KeyIsPressed('D')) {
				cam.pos.x += dTheta;
			}

			if (keyboard.KeyIsPressed(VK_LEFT)) {
				cam.dir.y += dTheta * dt;
			}
			if (keyboard.KeyIsPressed(VK_RIGHT)) {
				cam.dir.y -= dTheta * dt;
			}
			if (keyboard.KeyIsPressed(VK_UP)) {
				cam.dir.x -= dTheta * dt;
			}
			if (keyboard.KeyIsPressed(VK_DOWN)) {
				cam.dir.x += dTheta * dt;
			}
			if (keyboard.KeyIsPressed('Q')) {
				cam.dir.z += dTheta * dt;
			}
			if (keyboard.KeyIsPressed('E')) {
				cam.dir.z -= dTheta * dt;
			}


			gdi.startFrame();

			for (int i = 0; i < temp.indicies.size(); i+=3) {
				int i1 = temp.indicies[i];
				int i2 = temp.indicies[i+1];
				int i3 = temp.indicies[i+2];

				Vec3 c1 = temp.vertices[i1];
				Vec3 c2 = temp.vertices[i2];
				Vec3 c3 = temp.vertices[i3];

				c1 = Calculator::rotateAroundCenter(c1, cam.pos, cam.dir.x, cam.dir.y, cam.dir.z);
				c2 = Calculator::rotateAroundCenter(c2, cam.pos, cam.dir.x, cam.dir.y, cam.dir.z);
				c3 = Calculator::rotateAroundCenter(c3, cam.pos, cam.dir.x, cam.dir.y, cam.dir.z);

				gdi.drawTriangle(Vec2(c1.x, c1.y),
								 Vec2(c2.x, c2.y),
								 Vec2(c3.x, c3.y),
								 temp.color);

				gdi.drawLine(Vec2(c1.x, c1.y), Vec2(c2.x, c2.y), 0x000000);
				gdi.drawLine(Vec2(c2.x, c2.y), Vec2(c3.x, c3.y), 0x000000);
				gdi.drawLine(Vec2(c3.x, c3.y), Vec2(c1.x, c1.y), 0x000000);
			}

			for (MeshGDI eachMesh: meshes) {
				for (int i = 0; i < eachMesh.indicies.size(); i += 3) {
					int i1 = eachMesh.indicies[i];
					int i2 = eachMesh.indicies[i + 1];
					int i3 = eachMesh.indicies[i + 2];

					Vec3 c1 = eachMesh.vertices[i1];
					Vec3 c2 = eachMesh.vertices[i2];
					Vec3 c3 = eachMesh.vertices[i3];

					c1 = Calculator::rotateAroundCenter(c1, cam.pos, cam.dir.x, cam.dir.y, cam.dir.z);
					c2 = Calculator::rotateAroundCenter(c2, cam.pos, cam.dir.x, cam.dir.y, cam.dir.z);
					c3 = Calculator::rotateAroundCenter(c3, cam.pos, cam.dir.x, cam.dir.y, cam.dir.z);

					gdi.drawTriangle(Vec2(c1.x, c1.y),
									 Vec2(c2.x, c2.y),
									 Vec2(c3.x, c3.y),
									 eachMesh.color);

					gdi.drawLine(Vec2(c1.x, c1.y), Vec2(c2.x, c2.y), 0x000000);
					gdi.drawLine(Vec2(c2.x, c2.y), Vec2(c3.x, c3.y), 0x000000);
					gdi.drawLine(Vec2(c3.x, c3.y), Vec2(c1.x, c1.y), 0x000000);
				}
			}


			gdi.DrawFrame();

			break;
		}

	case Scene::GRAPHIC_TYPE::OPENGL: {
		//gOpengl.addVertices(temp.vertices, temp.indicies);


		GLfloat cameraSpeed = 5.0f * 0.01;
		if (keyboard.KeyIsPressed('W'))
			gOpengl.cameraPos += cameraSpeed * gOpengl.cameraFront;
		if (keyboard.KeyIsPressed('S'))
			gOpengl.cameraPos -= cameraSpeed * gOpengl.cameraFront;
		if (keyboard.KeyIsPressed('A'))
			gOpengl.cameraPos -= glm::normalize(glm::cross(gOpengl.cameraFront, gOpengl.cameraUp)) * cameraSpeed;
		if (keyboard.KeyIsPressed('D'))
			gOpengl.cameraPos += glm::normalize(glm::cross(gOpengl.cameraFront, gOpengl.cameraUp)) * cameraSpeed;




		
		std::vector<glm::vec3> newVert;

		for (int i = 0; i < tempSmall.vertices.size(); i++) {
			newVert.push_back(glm::vec3(tempSmall.vertices[i].x,
										tempSmall.vertices[i].y,
										tempSmall.vertices[i].z));
		}
		
		newVert.clear();
		for (MeshGDI eachMesh : meshes) {
			gOpengl.addMeshVerts(eachMesh);
		}
		
		gOpengl.addMeshVerts(tempSmall);

		gOpengl.draw();
		break;
	}

	default:
		break;
	}

}


void Scene::setUpScene() {

	tempSmall.color = 0xFF0000;

	const int height = 100;
	const int width = 100;

	bool flag = true;
	for (int i = 0; i < 8; i++) {// Lags at 50x50
		for (int j = 0; j < 8; j++) {
			int x = i * height;
			int y = j * width;
			int z = 0;
			if (flag) {
				//meshes.push_back(MeshGDI(i * height, j * width, 0, height, width, 0x606060));
				meshes.push_back(MeshGDI({ Vec3(x/100.0f, y / 100.0f, z / 100.0f),
										  Vec3((x + width) / 100.0f, y / 100.0f, z / 100.0f),
										  Vec3((x + width) / 100.0f, (y + height) / 100.0f, z / 100.0f),
										  Vec3(x / 100.0f, (y + height) / 100.0f, z / 100.0f) },
					{ 0, 1, 2, 0, 2, 3 },
					0x606060));
				//coords.add(new Coordinate(x, y, z));
				//coords.add(new Coordinate(x + width, y, z));
				//coords.add(new Coordinate(x + width, y + height, z));
				//coords.add(new Coordinate(x, y + height, z));

			}
			else {
				//meshes.push_back(MeshGDI(i * height, j * width, 0, height, width,0x373737));
				meshes.push_back(MeshGDI({ Vec3(x / 100.0f, y / 100.0f, z / 100.0f),
										  Vec3((x + width) / 100.0f, y / 100.0f, z / 100.0f),
										  Vec3((x + width) / 100.0f, (y + height) / 100.0f, z / 100.0f),
										  Vec3(x / 100.0f, (y + height) / 100.0f, z / 100.0f) },
					{ 0, 1, 2, 0, 2, 3 },
					0x303030));
			}
			flag = !flag;
		}
		flag = !flag;
	}
}
