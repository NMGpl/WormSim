#pragma once
#include "raylib.h"
#include <string>

class Input {
	int x, y;
	int width, height;
	Color color;
public:
	Input(int x, int y, int width, int height);
	void draw() const;
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	void setColor(Color color);
};

