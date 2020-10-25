#include "Vec2.h"

Vec2::Vec2(float x, float y)
	:x(x), y(y) {}


Vec2::Vec2(Vec3 vec) 
:x(vec.x), y(vec.y){}
