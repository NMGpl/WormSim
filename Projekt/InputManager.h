#pragma once
#include "raylib.h"

class InputManager {
public:
	bool isMouseOver(int x, int y, int width, int height) const;
	bool isLMouseClicked() const;
	bool isRMouseClicked() const;
	bool isLMousePressed() const;
	bool isLMouseReleased() const;
	bool isLShiftClicked() const;
};

