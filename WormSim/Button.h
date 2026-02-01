#pragma once
#include "raylib.h"
#include <string>

class Button {
	int x, y;
	int width, height;
	int size;
	bool toggled, toggleable;
	int id;
	Color color = WHITE, bgColor = BLACK, txtColor = WHITE;
	std::string buttonName;
public:
	Button(int x, int y, int width, int height, std::string str, int id, bool toggleable = false, bool toggled = false, int size = 30);
	void draw();
	void setColor(Color color);
	void setBgColor(Color color);
	void setTxtColor(Color color);
	void toggle();
	void setToggle(bool toggle);

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	int getID() const;
};

