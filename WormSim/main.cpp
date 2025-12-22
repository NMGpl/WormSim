#include "Graphics.h"
#include "Simulation.h"
#include "raylib.h"
#include <ctime>

int main(){
    srand(time(0));
    Simulation simulation(50, 40);
    Graphics g(simulation);
    Image image = LoadImage("icon.png");
    SetWindowIcon(image);

    while (!WindowShouldClose()) {
        g.begin();
        g.draw();
        g.end();
        simulation.simulate();
    }
    CloseWindow();
}