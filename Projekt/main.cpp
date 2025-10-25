#include "Board.h"
#include "Worm.h"
#include "SimulationConfig.h"
#include "Simulation.h"
#include <iostream>

int main(){
    Simulation simulation;
    simulation.start();
    while (true) {
        simulation.step();
        system("pause");
    }
    return 0;
}