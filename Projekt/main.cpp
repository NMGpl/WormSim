#include "Graphics.h"
#include "Simulation.h"
#include "raylib.h"
#include <ctime>

int main(){
    srand(time(0));
    Simulation simulation;
    Graphics g(simulation);
    //simulation.setup();
    while (!WindowShouldClose()) {
        // simulation.step();
        // system("pause");
        // system("cls");
        g.begin();
        g.draw();
        g.end();
    }
    // destroy the window and cleanup the OpenGL context
    CloseWindow();
}