#include "Input.h"

Input::Input(int x, int y, int width, int height, int value, int id) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	color = WHITE;
	this->activeValue = value;
	this->id = id;
	this->value = activeValue;
}

void Input::draw() const {
	int size = 24;
	std::string strValue = std::to_string(value);
	for (size; MeasureText(strValue.c_str(), size) >= width; size--);

	if (value != activeValue) {
		DrawRectangle(x, y, width, height, ColorFromHSV(360, 0.97, 0.43));
		DrawRectangleLines(x, y, width, height, color);
		DrawText(strValue.c_str(), x + (width / 2) - (MeasureText(strValue.c_str(), size) / 2), y, size, ColorFromHSV(360, 0.25, 1));
	}
	else {
		DrawRectangleLines(x, y, width, height, color);
		DrawText(strValue.c_str(), x + (width / 2) - (MeasureText(strValue.c_str(), size) / 2), y, size, WHITE);
	}
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

void Input::setActiveValue(int value) {
	this->activeValue = value;
}

int Input::getValue() const {
	return value;
}

void Input::setValue(int value) {
	this->value = value;
}