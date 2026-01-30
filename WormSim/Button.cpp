#include "Button.h"

Button::Button(int x, int y, int width, int height, std::string str, int id, Color color) : id(id) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->buttonName = str;
	this->color = color;
}

void Button::draw() const {
	int size = 30;
	float dY = 0;
	DrawRectangleLines(x, y, width, height, color);
	for (size; MeasureText(buttonName.c_str(), size) >= width; size--, dY += 0.5);
	DrawText(buttonName.c_str(), x + (width / 2) - (MeasureText(buttonName.c_str(), size) / 2), y + dY, size, WHITE);
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

int Button::getID() const {
	return id;
}