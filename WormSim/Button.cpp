#include "Button.h"

Button::Button(int x, int y, int width, int height, std::string str, int id, bool toggleable, bool toggled, int size) : id(id) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->buttonName = str;
	this->toggled = toggled;
	this->toggleable = toggleable;
	this->size = size;
	if (toggled) {
		this->bgColor = WHITE;
		this->txtColor = BLACK;
	}
}

void Button::draw() {
	int size = 30;
	if (this->size != size) size = this->size;
	float dY = 0;

	if (toggleable && toggled) {
		bgColor = WHITE;
		txtColor = BLACK;
	}
	else if(toggleable && !toggled) {
		bgColor = BLACK;
		txtColor = WHITE;
	}
	DrawRectangle(x, y, width, height, bgColor);
	DrawRectangleLines(x, y, width, height, color);
	for (size; MeasureText(buttonName.c_str(), size) >= width; size--, dY += 0.5);
	DrawText(buttonName.c_str(), x + (width / 2) - (MeasureText(buttonName.c_str(), size) / 2), y + dY, size, txtColor);
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

void Button::setToggle(bool toggle) {
	this->toggled = toggle;
}

void Button::toggle() {
	toggled = !toggled;
}

void Button::setColor(Color color) {
	this->color = color;
}

void Button::setBgColor(Color color) {
	this->bgColor = color;
}

void Button::setTxtColor(Color color) {
	this->txtColor = color;
}

int Button::getID() const {
	return id;
}