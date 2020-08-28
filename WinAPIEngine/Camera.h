#pragma once

#include "Vec3.h"
#include <math.h>


class Camera {
public:
	Vec3 pos;
	Vec3 dir;

	//near, far

	Camera(Vec3 pos, Vec3 dir);

	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
};

