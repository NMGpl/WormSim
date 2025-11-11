#include "Input.h"
#include <string>

Input::Input(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	color = WHITE;
}

void Input::draw() const {
	DrawRectangleLines(x, y, width, height, color);
}

int Input::getX() const {
	return x;
}
int Input::getY() const {
	return y;
}
int Input::getWidth() const {
	return width;
}
int Input::getHeight() const {
	return height;
}

void Input::setColor(Color color) {
	this->color = color;
}