#pragma once
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Vec3{
public:
	float x;
	float y;
	float z;

	Vec3(float x, float y, float z);

	Vec3(glm::vec3 vec);
};