#include "Calculator.h"

Vec3 Calculator::rotateAroundCenter(Vec3 coord, Vec3 center,
	float xAngle, float yAngle, float zAngle) {

	Vec3 rot = Vec3(coord.x - center.x,
					coord.y - center.y,
					coord.z - center.z);
	
	rot = Mat3::mutltply(rot, Mat3::RotationX(xAngle));
	rot = Mat3::mutltply(rot, Mat3::RotationY(yAngle));
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

	rot = Mat3::mutltply(rot, Mat3::RotationX(direction.x));
	rot = Mat3::mutltply(rot, Mat3::RotationY(direction.y));
	rot = Mat3::mutltply(rot, Mat3::RotationZ(direction.z));

	rot.x /= (rot.z / 620);
	rot.y /= (rot.z / 620);


	rot.x += (640.0 / 2.0);
	rot.y += (480.0 / 2.0);

	//divide by z/cam.near

	//offset?

	return rot;
}
