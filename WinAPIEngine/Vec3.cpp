#include "Vec3.h"

Vec3::Vec3(float x, float y, float z)
:x(x), y(y), z(z){}

Vec3::Vec3(glm::vec3 vec)
   :x(vec.x), y(vec.y), z(vec.z) {}
