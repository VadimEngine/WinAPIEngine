#include "Scene.h"
#include "Camera.h"

int Scene::SceneCount = 0;

Scene::Scene() {
	//setUpScene();
	this->name = "Scene " + std::to_string(SceneCount++);
}

void Scene::drawScene(GRAPHIC_TYPE graphicType, GraphicsGDI& gdi, GraphicsD3D& d3d,
	GraphicsOpenGL& gOpengl, Mouse& mouse, Keyboard& keyboard, CustomTimer& timer, CameraD3D& theCam) {

	switch (graphicType) {
		case Scene::GRAPHIC_TYPE::DIRECT3D: {
			break;
		}
		case Scene::GRAPHIC_TYPE::CUSTOM: {
			float dTheta = 1;
			const float dt = 1.0f / 60.0f;
			static Camera theCam;
			if (keyboard.KeyIsPressed('W')) {
				theCam.moveForward(dt);
			}
			if (keyboard.KeyIsPressed('A')) {
				theCam.pos.x -= dTheta * dt;
			}
			if (keyboard.KeyIsPressed('S')) {
				theCam.moveBack(dt);
			}
			if (keyboard.KeyIsPressed('D')) {
				theCam.pos.x += dTheta * dt;
			}
			if (keyboard.KeyIsPressed(VK_LEFT)) {
				theCam.dir.y += dTheta * dt;
			}
			if (keyboard.KeyIsPressed(VK_RIGHT)) {
				theCam.dir.y -= dTheta * dt;
			}
			if (keyboard.KeyIsPressed(VK_UP)) {
				theCam.dir.x -= dTheta * dt;
			}
			if (keyboard.KeyIsPressed(VK_DOWN)) {
				theCam.dir.x += dTheta * dt;
			}
			if (keyboard.KeyIsPressed('Q')) {
				theCam.dir.z += dTheta * dt;
			}
			if (keyboard.KeyIsPressed('E')) {
				theCam.dir.z -= dTheta * dt;
			}
			//Move this outside of the loop
			gdi.setCamera(&theCam);

			gdi.startFrame();
			
			//renderable.renderCustom(gdi, theCam);

			for (unsigned int i = 0; i < renderableMeshes.size(); i++) {
				//renderableMeshes[i].renderCustom(gdi, theCam);
				gdi.drawMesh(renderableMeshes[i]);
			}
			gdi.drawFrame();
			break;
		}

	case Scene::GRAPHIC_TYPE::OPENGL: {
		GLfloat cameraSpeed = 5.0f * 0.01;
		if (keyboard.KeyIsPressed('W'))
			gOpengl.cameraPos += cameraSpeed * gOpengl.cameraFront;
		if (keyboard.KeyIsPressed('S'))
			gOpengl.cameraPos -= cameraSpeed * gOpengl.cameraFront;
		if (keyboard.KeyIsPressed('A'))
			gOpengl.cameraPos -= glm::normalize(glm::cross(gOpengl.cameraFront, gOpengl.cameraUp)) * cameraSpeed;
		if (keyboard.KeyIsPressed('D'))
			gOpengl.cameraPos += glm::normalize(glm::cross(gOpengl.cameraFront, gOpengl.cameraUp)) * cameraSpeed;

		static Camera theCam;
		//Move this outside the loop
		gOpengl.setCamera(&theCam);
		gOpengl.clearVertices();
		gOpengl.startFrame();

		//renderable.renderOpenGL(gOpengl, theCam);
		for (unsigned int i = 0; i < renderableMeshes.size(); i++) {
			//renderableMeshes[i].renderOpenGL(gOpengl, theCam);
			gOpengl.drawMesh(renderableMeshes[i]);
		}

		gOpengl.drawFrame();
		break;
	}

	default:
		break;
	}
}


void Scene::setUpScene() {
	const float height = .5f;
	const float width = .5f;

	bool flag = true;
	for (unsigned int i = 0; i < 8; i++) {// Lags at 50x50
		for (unsigned int j = 0; j < 8; j++) {
			float x = i * height;
			float y = j * width;
			float z = 0;
			if (flag) {
				addMesh(RenderableMesh({glm::vec3(x, y, z),
										glm::vec3(x + width, y, z),
										glm::vec3(x + width, y + height, z),
										glm::vec3(x, y + height, z) },
										{0, 1, 2, 0 ,2, 3}, 0x606060));
			} else {
				addMesh(RenderableMesh({glm::vec3(x, y, z),
										glm::vec3(x + width, y, z),
										glm::vec3(x + width, y + height, z),
										glm::vec3(x, y + height, z) },
										{ 0, 1, 2, 0 ,2, 3 }, 0x303030));
			}
			flag = !flag;
		}
		flag = !flag;
	}

	//renderableMeshes.push_back(RenderableMesh("Images\\ExportableFox.obj", 0xFF0000));
	
	addMesh(RenderableMesh("Images\\ExportableFox.obj", 0xFF0000));
}

void Scene::update(float dt, Mouse& mouse, Keyboard& keyboard) {
	//poll events from mouse and keyboard

	float dTheta = 1;
	dt = 1.0f / 60.0f;
	GLfloat cameraSpeed = 5.0f * 0.01;

	if (keyboard.KeyIsPressed('W')) {
		theCamera.moveForward(dt);
		theCamera.cameraPos += cameraSpeed * theCamera.cameraFront;
	}
	if (keyboard.KeyIsPressed('A')) {
		theCamera.pos.x -= dTheta * dt;
		theCamera.cameraPos -= glm::normalize(glm::cross(theCamera.cameraFront, theCamera.cameraUp)) * cameraSpeed;
	}
	if (keyboard.KeyIsPressed('S')) {
		theCamera.moveBack(dt);
		theCamera.cameraPos -= cameraSpeed * theCamera.cameraFront;

	}
	if (keyboard.KeyIsPressed('D')) {
		theCamera.pos.x += dTheta * dt;
		theCamera.cameraPos += glm::normalize(glm::cross(theCamera.cameraFront, theCamera.cameraUp)) * cameraSpeed;
	}

	if (keyboard.KeyIsPressed(VK_LEFT)) {
		theCamera.dir.y += dTheta * dt;
	}
	if (keyboard.KeyIsPressed(VK_RIGHT)) {
		theCamera.dir.y -= dTheta * dt;
	}
	if (keyboard.KeyIsPressed(VK_UP)) {
		theCamera.dir.x -= dTheta * dt;
	}
	if (keyboard.KeyIsPressed(VK_DOWN)) {
		theCamera.dir.x += dTheta * dt;
	}
	if (keyboard.KeyIsPressed('Q')) {
		theCamera.dir.z += dTheta * dt;
	}
	if (keyboard.KeyIsPressed('E')) {
		theCamera.dir.z -= dTheta * dt;
	}
}

void Scene::render(AbstractGraphics* theGraphics, Mouse& mouse, Keyboard& keyboard) {
	//poll events from mouse and keyboard

	//Draw
	theGraphics->setCamera(&theCamera);
	theGraphics->startFrame();

	for (unsigned int i = 0; i < renderableMeshes.size(); i++) {
		theGraphics->drawMesh(renderableMeshes[i]);
	}

	theGraphics->drawString(theGraphics->toString(), 0, 0);
	theGraphics->drawString(this->name, 0, 5 + 8);

	theGraphics->drawFrame();
}

void Scene::setCamera(Camera* theCamera) {

}

void Scene::addMesh(RenderableMesh theMesh) {
	renderableMeshes.push_back(theMesh);
}

std::string Scene::toString() {
	std::ostringstream stringBuild;

	stringBuild << "Scene Meshes: " << renderableMeshes.size();
	return stringBuild.str();
}

void Scene::setName(std::string theName) {
	this->name = theName;
}

void Scene::drawDirect3D(GraphicsD3D* theGraphics, Mouse& mouse, Keyboard& keyboard) {
	float dTheta = 1;
	const float dt = 1.0f / 60.0f;
	GLfloat cameraSpeed = 5.0f * 0.01;

	if (keyboard.KeyIsPressed('W')) {
		theCamera.moveForward(dt);
		theCamera.cameraPos += cameraSpeed * theCamera.cameraFront;
	}
	if (keyboard.KeyIsPressed('A')) {
		theCamera.pos.x -= dTheta * dt;
		theCamera.cameraPos -= glm::normalize(glm::cross(theCamera.cameraFront, theCamera.cameraUp)) * cameraSpeed;
	}
	if (keyboard.KeyIsPressed('S')) {
		theCamera.moveBack(dt);
		theCamera.cameraPos -= cameraSpeed * theCamera.cameraFront;

	}
	if (keyboard.KeyIsPressed('D')) {
		theCamera.pos.x += dTheta * dt;
		theCamera.cameraPos += glm::normalize(glm::cross(theCamera.cameraFront, theCamera.cameraUp)) * cameraSpeed;
	}

	if (keyboard.KeyIsPressed(VK_LEFT)) {
		theCamera.dir.y += dTheta * dt;
	}
	if (keyboard.KeyIsPressed(VK_RIGHT)) {
		theCamera.dir.y -= dTheta * dt;
	}
	if (keyboard.KeyIsPressed(VK_UP)) {
		theCamera.dir.x -= dTheta * dt;
	}
	if (keyboard.KeyIsPressed(VK_DOWN)) {
		theCamera.dir.x += dTheta * dt;
	}
	if (keyboard.KeyIsPressed('Q')) {
		theCamera.dir.z += dTheta * dt;
	}
	if (keyboard.KeyIsPressed('E')) {
		theCamera.dir.z -= dTheta * dt;
	}
	
	
	//theGraphics->BeginFrame(0.07f, 0.0f, 0.12f);

	theGraphics->setCamera(&theCamera);
	theGraphics->startFrame();

	//static float temp = math.
	static CustomTimer timer;
	const auto dt2 = timer.Peek() * 1.0f;
	float temp = sin(dt);


	float camAngle = theCamera.cameraFront.x;
	float camX = theCamera.cameraPos.x;
	float camY = theCamera.cameraPos.y;
	float camZ = theCamera.cameraPos.z;


	//theGraphics->drawImageTemp(camAngle, camX, camZ);

	std::string theString = "Direct3D";

	float x = 0;
	float y = 0;

	x = (x - (640.0f / 2.0f)) / (640.0f / 2.0f);
	y = -(y - (480.0f / 2.0f)) / (480 / 2.0f);


	for (unsigned int i = 0; i < renderableMeshes.size(); i++) {
		theGraphics->drawMesh(renderableMeshes[i]);
		//theGraphics->drawMesh(renderableMeshes[i], 0,0,0, dt2);
	}

	//draw without rotation
	theGraphics->drawString(theString, 0, 0);//-1, .8

	//theGraphics->drawImage();

	theGraphics->drawFrame();
}
