#include "InputManager.h"

bool InputManager::isMouseOver(int x, int y, int width, int height) const {
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();
	if (mouseX > x && mouseX < x + width && mouseY > y && mouseY < y + height) {
		return true;
	}
	return false;
}

bool InputManager::isLMouseClicked() const {
	bool click = IsMouseButtonPressed(0);
	if (click) {
		return true;
	}
	return false;
}

bool InputManager::isRMouseClicked() const {
	bool click = IsMouseButtonPressed(1);
	if (click) {
		return true;
	}
	return false;
}

bool InputManager::isLMousePressed() const {
	bool press = IsMouseButtonDown(0);
	if (press) {
		return true;
	}
	return false;
}

bool InputManager::isLMouseReleased() const {
	bool release = IsMouseButtonReleased(0);
	if (release) {
		return true;
	}
	return false;
}

bool InputManager::isLShiftClicked() const {
	bool press = IsKeyDown(KEY_LEFT_SHIFT);
	if (press) {
		return true;
	}
	return false;
}