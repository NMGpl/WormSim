#include "Button.h"
#include <string>

void Button::draw(int x, int y, int width, int height, Color color, std::string str) const {
	DrawRectangleLines(x, y, width, height, color);
	int size = 20;
	for (size; MeasureText(str.c_str(), size) >= width; size--);
	DrawText(str.c_str(), x + (width / 2) - (MeasureText(str.c_str(), size) / 2), y, size, WHITE);
}