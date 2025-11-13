#include "InputManager.h"
#include "raylib.h"

bool InputManager::isMouseOver(int x, int y, int width, int height) {
	int mouseX = GetMouseX();
	int mouseY = GetMouseY();
	if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
		return true;
	}
	return false;
}

bool InputManager::isLMouseClicked() {
	bool click = IsMouseButtonPressed(0);
	if (click) {
		return true;
	}
	return false;
}

bool InputManager::isRMouseClicked() {
	bool click = IsMouseButtonPressed(1);
	if (click) {
		return true;
	}
	return false;
}

bool InputManager::isLMousePressed() {
	bool press = IsMouseButtonPressed(0);
	if (press) {
		return true;
	}
	return false;
}

bool InputManager::isLMouseReleased() {
	bool release = IsMouseButtonReleased(0);
	if (release) {
		return true;
	}
	return false;
}