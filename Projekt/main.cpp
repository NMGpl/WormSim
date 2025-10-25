#include "Simulation.h"
#include <iostream>

int main(){
    Simulation simulation;
    simulation.setup();
    //simulation.printConfig();
    while (true) {
        simulation.step();
        system("pause");
    }
    return 0;
}