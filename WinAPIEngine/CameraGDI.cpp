#include "CameraGDI.h"


CameraGDI::CameraGDI(Vec3 pos, Vec3 dir)
	:pos(pos), dir(dir) {}

void CameraGDI::moveForward() {
	float speed = 3;

	const float sinX = sin(dir.x);
	const float cosX = cos(dir.x);
	const float sinY = sin(dir.y);
	const float cosY = cos(dir.y);
	const float sinZ = sin(dir.z);
	const float cosZ = cos(dir.z);

	pos.x += sinX * cosY * (speed);
	pos.y += sinX * sinY * (speed);
	pos.z += cosX * (speed);
}

void CameraGDI::moveBack() {
	float speed = 3;

	const float sinX = sin(dir.x);
	const float cosX = cos(dir.x);
	const float sinY = sin(dir.y);
	const float cosY = cos(dir.y);
	const float sinZ = sin(dir.z);
	const float cosZ = cos(dir.z);

	pos.x -= sinX * cosY * (speed);
	pos.y -= sinX * sinY * (speed);
	pos.z -= cosX * (speed);
}

void CameraGDI::moveLeft() {

}

void CameraGDI::moveRight() {

}

void CameraGDI::moveUp() {

}

void CameraGDI::moveDown() {

}