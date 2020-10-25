#pragma once

#include "Vec3.h"
#include <math.h>


class CameraGDI {
public:
	Vec3 pos;
	Vec3 dir;

	//near, far

	CameraGDI(Vec3 pos, Vec3 dir);

	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
};

