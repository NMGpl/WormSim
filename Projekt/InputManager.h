#pragma once
class InputManager {
public:
	bool isMouseOver(int x, int y, int width, int height);
	bool isLMouseClicked();
	bool isRMouseClicked();
	bool isLMousePressed();
	bool isLMouseReleased();
	bool isLShiftClicked();
};

