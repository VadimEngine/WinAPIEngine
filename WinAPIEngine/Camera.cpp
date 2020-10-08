#include "Camera.h"

Camera::Camera():
    pos(0,0.0f,0.0f), dir(0,0,0){

}

void Camera::moveForward(float dt) {
	float speed = 3 * dt;

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

void Camera::moveBack(float dt) {
	float speed = 3 * dt;

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