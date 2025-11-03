#include "Simulation.h"

int main(){
    Simulation simulation;
    simulation.setup();
    //simulation.printConfig();
    while (true) {
        simulation.step();
        system("pause");
        system("cls");
    }
    return 0;
}