#pragma once
#include <string>
#include "raylib.h"

class Button {
	int x, y;
	int width, height;
	bool state;
	Color color, bgColor;
	std::string buttonName, id;
public:
	Button(int x, int y, int width, int height, std::string str, Color color = WHITE);
	void draw() const;
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	void setColor(Color color);
	std::string getID();
};

