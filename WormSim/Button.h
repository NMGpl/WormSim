#pragma once
#include "raylib.h"
#include <string>

class Button {
	int x, y;
	int width, height;
	bool state;
	int id;
	Color color, bgColor;
	std::string buttonName;
public:
	Button(int x, int y, int width, int height, std::string str, int id, Color color = WHITE);
	void draw() const;
	void setColor(Color color);

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	int getID() const;
};

