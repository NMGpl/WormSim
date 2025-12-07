#include "Worm.h"
#include <iostream>

Worm::Worm(int headX, int headY, int maxAge, int maxHunger, int maxSize, int maxProductivity) {
    this->maxAge = maxAge;
    this->maxHunger = maxHunger;
    this->maxSize = maxSize;
    this->maxProductivity = maxProductivity;
    this->headX = headX;
    this->headY = headY;
    this->movement = {};
    this->segments = {};
    age = 0;
    hunger = maxHunger / 2;
    size = 0;
    dead = false;
}

void Worm::move() {
    if (size != 0) {
        moveSegments();
    }
    std::vector <int> newPos = movement.back();
    this->headX = newPos[0];
    this->headY = newPos[1];
    movement.pop_back();
}

void Worm::moveSegments() {
    for (int i = size - 1; i > 0; i--) {
        segments[i][0] = segments[i - 1][0];
        segments[i][1] = segments[i - 1][1];
    }
    segments[0][0] = headX;
    segments[0][1] = headY;
}

std::vector <std::vector <int>> Worm::getMovement() const {
    return movement;
}

void Worm::setMovement(std::vector <std::vector <int>> movement) {
    this->movement = movement;
}

int Worm::getHeadX() const {
    return headX;
}

int Worm::getHeadY() const {
    return headY;
}

void Worm::setHeadCords(int headX, int headY) {
    this->headX = headX;
    this->headY = headY;
}

void Worm::die() {
    this->dead = true;
}

bool Worm::isDead() const{
    return dead;
}

void Worm::ageUp() {
    age += 1;
}

int Worm::getMaxAge() const {
    return maxAge;
}

void Worm::setMaxAge(int maxAge) {
    this->maxAge = maxAge;
}

int Worm::getAge() const {
    return age;
}

void Worm::setAge(int age) {
    this->age = age;
}

int Worm::getMaxHunger() const {
    return maxHunger;
}

void Worm::setMaxHunger(int maxHunger) {
    this->maxHunger = maxHunger;
}

int Worm::getHunger() const {
    return hunger;
}

void Worm::setHunger(int hunger) {
    this->hunger = hunger;
}

void Worm::modifyHunger(int hungerChange) {
    this->hunger += hungerChange;
}

void Worm::modifyAge(int ageChange) {
    this->age += ageChange;
}

void Worm::grow() {
    if (segments.empty()) {
        segments.push_back({ headX, headY });
    } else {
        std::vector <int> tail = segments.back();
        segments.push_back({ tail[0], tail[1] });
    }
    modifySize(1);
}

void Worm::modifySize(int sizeChange) {
    this->size += sizeChange;
}

int Worm::getMaxSize() const {
    return maxSize;
}

void Worm::setMaxSize(int maxSize) {
    this->maxSize = maxSize;
}

int Worm::getSize() const {
    return this->size;
}

void Worm::setMaxProductivity(int maxProductivity) {
    this->maxProductivity = maxProductivity;
}

int Worm::getMaxProductivity() {
    return maxProductivity;
}

std::vector <std::vector <int>> Worm::getSegments() {
    return segments;
}