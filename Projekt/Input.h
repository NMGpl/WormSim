#pragma once
#include "raylib.h"
#include <string>

class Input {
	int x, y;
	int width, height;
public:
	void draw(int x, int y, int width, int height, Color color) const;
};

