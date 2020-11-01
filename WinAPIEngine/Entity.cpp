#include "Entity.h"


Entity::Entity(int x, int y, int width, int height)
:x(x), y(y), height(height), width(width){}

int Entity::getX() {
	return x;
}

int Entity::getY() {
	return y;
}
int Entity::getWidth() {
	return width;
}
int Entity::getHeight() {
	return height;
}

void Entity::update(Keyboard& kbd) {
	if (kbd.KeyIsPressed('W')) {
		y-=10;
	}
	if (kbd.KeyIsPressed('S')) {
		y+= 10;
	}
	if (kbd.KeyIsPressed('A')) {
		x-= 10;
	}
	if (kbd.KeyIsPressed('D')) {
		x+= 10;
	}
}
