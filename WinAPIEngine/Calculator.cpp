#include "Calculator.h"
#include <numbers>

Vec3 Calculator::rotateAroundCenter(Vec3 coord, Vec3 center,
	float xAngle, float yAngle, float zAngle) {

	Vec3 rot = Vec3(coord.x - center.x,
					coord.y - center.y,
					coord.z - center.z);
	
	rot = Mat3::mutltply(rot, Mat3::RotationY(yAngle));
	rot = Mat3::mutltply(rot, Mat3::RotationX(xAngle));
	rot = Mat3::mutltply(rot, Mat3::RotationZ(zAngle));

	rot.x /= (rot.z / 620);
	rot.y /= (rot.z / 620);


	rot.x += (640.0 / 2.0);
	rot.y += (480.0 / 2.0);

	//divide by z/cam.near

	//offset?

	return rot;
}


Vec3 Calculator::rotateAroundCenter(Vec3 coord, Vec3 center, Vec3 direction) {
	Vec3 rot = Vec3(coord.x - center.x,
		coord.y - center.y,
		coord.z - center.z);

	//rot = Mat3::mutltply(rot, Mat3::RotationX(direction.x));// XY
	//rot = Mat3::mutltply(rot, Mat3::RotationZ(direction.z));// XZ
	//rot = Mat3::mutltply(rot, Mat3::RotationY(direction.y));// ZY

	rot = Mat3::mutltply(rot, Mat3::RotationX3(direction.x));// XY
	rot = Mat3::mutltply(rot, Mat3::RotationZ3(direction.z));// XZ
	rot = Mat3::mutltply(rot, Mat3::RotationY3(direction.y));// ZY

	rot.x /= (rot.z / 620);
	rot.y /= (rot.z / 620);


	rot.x += (640.0 / 2.0);
	rot.y += (480.0 / 2.0);

	//divide by z/cam.near

	//offset?

	return rot;
}

float Calculator::zOnPlane(Vec3 c1, Vec3 c2, Vec3 c3, float x, float y) {
	float ax = c1.x - c2.x;
	float ay = c1.y - c2.y;
	float az = c1.z - c2.z;

	float bx = c1.x - c3.x;
	float by = c1.y - c3.y;
	float bz = c1.z - c3.z;

	float nx = (ay * bz) - (az * by);
	float ny = -((ax * bz) - (az * bx));
	float nz = (ax * by) - (ay * bx);

	float tempx = nx * (x - c1.x);
	float tempy = ny * (y - c1.y);
	float tempz = nz * c1.z;

	float z = ((tempx)+(tempy)-(tempz)) / (-nz);

	return z;
}
