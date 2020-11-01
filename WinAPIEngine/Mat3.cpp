#include "Mat3.h"


Mat3 Mat3::RotationZ(float theta) {
	const float sinTheta = sin(theta);
	const float cosTheta = cos(theta);
	return{
		 cosTheta, sinTheta, 0.0,
		-sinTheta, cosTheta, 0.0,
		0.0,    0.0,   1.0
	};
}

Mat3 Mat3::RotationZ2(float theta) {
	const float sinTheta = sin(theta);
	const float cosTheta = cos(theta);
	return{
		1.0, 0.0, 0.0,
		0, cosTheta, sinTheta,
		0.0, -sinTheta, cosTheta
	};
}


Mat3 Mat3::RotationY(float theta) {
	const float sinTheta = sin(theta);
	const float cosTheta = cos(theta);
	return{
		 cosTheta, 0.0,-sinTheta,
		 0.0,   1.0, 0.0,
		 sinTheta, 0.0, cosTheta
	};
}

Mat3 Mat3::RotationX(float theta) {
	const float sinTheta = sin(theta);
	const float cosTheta = cos(theta);
	return{
		1.0, 0.0,   0.0,
		0.0, cosTheta, sinTheta,
		0.0,-sinTheta, cosTheta,
	};
}

Vec3 Mat3::mutltply(Vec3 m1, Mat3 m2) {
	Vec3 result(0, 0, 0);
	result.x = m1.x * m2.elements[0][0] + m1.y * m2.elements[1][0] + m1.z * m2.elements[2][0];
	result.y = m1.x * m2.elements[0][1] + m1.y * m2.elements[1][1] + m1.z * m2.elements[2][1];
	result.z = m1.x * m2.elements[0][2] + m1.y * m2.elements[1][2] + m1.z * m2.elements[2][2];
	return result;
}