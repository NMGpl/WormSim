#include "Worm.h"
#include <iostream>

void Worm::initializeWorm() {

}

void Worm::ageUp() {
    this->age += 1;
    if (this->age > 10) {
        
    }
    std::cout << this->age;
}
