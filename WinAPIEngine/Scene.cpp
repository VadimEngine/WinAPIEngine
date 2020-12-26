#include "Scene.h"
#include "Camera.h"

int Scene::SceneCount = 0;

Scene::Scene() {
	//setUpScene();
	this->name = "Scene " + std::to_string(SceneCount++);
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
	//dt = 1.0f / 60.0f;
	GLfloat cameraSpeed = 5.0f * 0.01;

	if (keyboard.KeyIsPressed('W')) {
		theCamera.moveForward(dt);
		theCamera.cameraPos += cameraSpeed * theCamera.cameraFront;
	}
	if (keyboard.KeyIsPressed('A')) {
		//theCamera.pos.x -= dTheta * dt;
		theCamera.moveLeft(dt);
		theCamera.cameraPos -= glm::normalize(glm::cross(theCamera.cameraFront, theCamera.cameraUp)) * cameraSpeed;
	}
	if (keyboard.KeyIsPressed('S')) {
		theCamera.moveBack(dt);
		theCamera.cameraPos -= cameraSpeed * theCamera.cameraFront;

	}
	if (keyboard.KeyIsPressed('D')) {
		//theCamera.pos.x += dTheta * dt;
		theCamera.moveRight(dt);
		
		theCamera.cameraPos += glm::normalize(glm::cross(theCamera.cameraFront, theCamera.cameraUp)) * cameraSpeed;
	}

	if (keyboard.KeyIsPressed(VK_LEFT)) {
		theCamera.rotateLeft(dt);
		//theCamera.dir.y += dTheta * dt;
	}
	if (keyboard.KeyIsPressed(VK_RIGHT)) {
		theCamera.rotateRight(dt);
		//theCamera.dir.y -= dTheta * dt;
	}
	if (keyboard.KeyIsPressed(VK_UP)) {
		theCamera.rotateUp(dt);
		//theCamera.dir.x -= dTheta * dt;
	}
	if (keyboard.KeyIsPressed(VK_DOWN)) {
		theCamera.rotateDown(dt);
		//theCamera.dir.x += dTheta * dt;
	}
	if (keyboard.KeyIsPressed('Q')) {
		theCamera.rotateCounterClockwise(dt);
	}
	if (keyboard.KeyIsPressed('E')) {
		theCamera.rotateClockwise(dt);
	}

	if (keyboard.KeyIsPressed(VK_SPACE)) {
		theCamera.moveUp(dt);
	}

	if (keyboard.KeyIsPressed(VK_SHIFT)) {
		theCamera.moveDown(dt);
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