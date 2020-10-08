#pragma once

#include "Vec3.h"
#include "Mat3.h"

class Calculator {
private:
	Calculator();
public:

	static Vec3 rotateAroundCenter(Vec3 coord, Vec3 center,
		float xAngle, float yAngle, float zAngle);

	static Vec3 rotateAroundCenter(Vec3 coord, Vec3 center,
		Vec3 direction);

};

