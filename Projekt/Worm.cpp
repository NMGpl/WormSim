#include "Worm.h"
#include <iostream>

Worm::Worm() {
    age = 0;
    hunger = 0;
    size = 0;
}

Worm::~Worm() {
    std::cout << "What the sigma?";
}

void Worm::initializeWorm() {

}

bool Worm::isDead() const{
    return age > maxAge;
}

void Worm::ageUp() {
    age += 1;
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