#pragma once
#include <string>
#include "raylib.h"

class Button {
	int x, y;
	int width, height;
	std::string buttonName;
public:
	void draw(int x, int y, int width, int height, Color color, std::string str) const;
};

