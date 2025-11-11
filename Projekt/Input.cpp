#include "Input.h"
#include <string>

void Input::draw(int x, int y, int width, int height, Color color) const {
	DrawRectangleLines(x, y, width, height, color);
}