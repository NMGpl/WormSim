#include "Button.h"
#include <string>

void Button::draw(int x, int y, int width, int height, Color color, std::string str) const {
	DrawRectangleLines(x, y, width, height, color);
}