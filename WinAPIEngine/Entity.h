#pragma once
#include "CustomWinHeader.h"
#include "Keyboard.h"

class Entity {
private:
	int x;
	int y;
	int width;
	int height;
public:
	Entity(int x, int y, int width, int height);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void update(Keyboard& kbd);
};