#pragma once
#include <string>
#include "raylib.h"

class Button {
	int x, y;
	int width, height;
	Color color;
	std::string buttonName;
public:
	Button(int x, int y, int width, int height, std::string str, Color color = WHITE);
	void draw() const;
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	void setColor(Color color);
};

