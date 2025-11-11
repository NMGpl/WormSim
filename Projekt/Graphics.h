#pragma once
#include "Button.h"
#include <vector>

class Graphics {
	int x, y;
	Button bHunger, bRegen, bSize, bLifespan;
	std::vector<Button> buttons = {bHunger, bRegen, bSize, bLifespan};
	void drawMenu() const;
	void drawWormBox() const;
public:
	Graphics(int x = 1280, int y = 720);
	void begin() const;
	void end() const;
	void draw() const;
};

