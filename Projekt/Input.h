#pragma once
#include "raylib.h"
#include <string>

class Input {
	int x, y;
	int width, height;
	int value, id;
	Color color;
public:
	Input(int x, int y, int width, int height, int value, int id);
	void draw() const;
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	void setColor(Color color);
	int getValue() const;
	void setValue(int value);
	int getID() const;
};

