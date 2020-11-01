#pragma once

#include "Vec3.h"
#include <math.h>

class Mat3 {
public:
	float elements[3][3];

	static Mat3 RotationZ(float theta);

	static Mat3 RotationZ2(float theta);

	static Mat3 RotationY(float theta);
	static Mat3 RotationX(float theta);

	static Vec3 mutltply(Vec3 m0, Mat3 m1);
};

