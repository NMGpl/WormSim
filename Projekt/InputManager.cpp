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