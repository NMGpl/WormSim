#pragma once
#include "Button.h"
#include "Input.h"
#include <vector>
#include <string>

class Graphics {
	int x, y;
	Button bRegen, bHunger, bSize, bLifespan, bChildren, bProductivity;
	Input iRegen, iHunger, iSize, iLifespan, iChildren, iProductivity;
	std::vector<Button> buttons = {bRegen, bHunger, bSize, bLifespan, bChildren, bProductivity};
	std::vector<Input> inputs = {iRegen, iHunger, iSize, iLifespan, iChildren, iProductivity};
	void drawMenu() const;
	void drawWormBox() const;
	void drawButtons(int startX, int startY, int width, int height, Color color = WHITE) const;
	void drawInputs(int startX, int startY, int width, int height, Color color = WHITE) const;
public:
	Graphics(int x = 1280, int y = 720);
	void begin() const;
	void end() const;
	void draw() const;
};

