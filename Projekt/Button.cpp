#include "Button.h"
#include <string>

Button::Button(int x, int y, int width, int height, std::string str, Color color) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->buttonName = str;
	this->color = color;
}

void Button::draw() const {
	//DrawRectangle(x, y, width, height, color);
	DrawRectangleLines(x, y, width, height, color);
	int size = 20;
	for (size; MeasureText(buttonName.c_str(), size) >= width; size--);
	DrawText(buttonName.c_str(), x + (width / 2) - (MeasureText(buttonName.c_str(), size) / 2), y, size, WHITE);
}

int Button::getX() const {
	return x;
}
int Button::getY() const {
	return y;
}
int Button::getWidth() const {
	return width;
}
int Button::getHeight() const {
	return height;
}

void Button::setColor(Color color) {
	this->color = color;
}