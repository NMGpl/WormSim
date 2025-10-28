#include "Worm.h"
#include <iostream>

Worm::Worm() {
    age = 0;
    hunger = 0;
    size = 0;
    maxAge = 0;
    maxHunger = 0;
    maxSize = 0;
}

Worm::~Worm() {
    std::cout << "What the sigma?";
}

void Worm::initializeWorm() {

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

int Worm::getMaxSize() const {
    return maxSize;
}

void Worm::setMaxSize(int maxSize) {
    this->maxSize = maxSize;
}