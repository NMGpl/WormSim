#include "Worm.h"
#include <iostream>

Worm::Worm(int headX, int headY, int maxAge, int maxHunger, int maxSize) {
    age = 0;
    hunger = 0;
    size = 0;
    this->maxAge = maxAge;
    this->maxHunger = maxHunger;
    this->maxSize = maxSize;
    this->headX = headX;
    this->headY = headY;
    this->movement = {};
}

void Worm::move() {
    
    std::vector <int> newPos = movement.back();
    this->headX = newPos[0];
    this->headY = newPos[1];
    movement.pop_back();
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

bool Worm::isDead() const{
    if (age > maxAge) return true;
    if (hunger > maxHunger) return true;
    return false;
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

int Worm::getMaxSize() const {
    return maxSize;
}

void Worm::setMaxSize(int maxSize) {
    this->maxSize = maxSize;
}