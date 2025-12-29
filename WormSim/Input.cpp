#include "Input.h"

Input::Input(int x, int y, int width, int height, int value, int id) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	color = WHITE;
	this->value = value;
	this->id = id;
}

void Input::draw() const {
	int size = 30;
	std::string strValue = std::to_string(value);
	DrawRectangleLines(x, y, width, height, color);
	for (size; MeasureText(strValue.c_str(), size) >= width; size--);
	DrawText(strValue.c_str(), x + (width / 2) - (MeasureText(strValue.c_str(), size) / 2), y, size, WHITE);
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

int Input::getId() const {
	return id;
}

void Input::setColor(Color color) {
	this->color = color;
}

int Input::getValue() const {
	return value;
}

void Input::setValue(int value) {
	this->value = value;
}