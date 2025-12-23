#include "Graphics.h"
#include "Simulation.h"
#include "raylib.h"
#include <ctime>

int main(){
    srand(time(0));
    Simulation s(6, 10);
    Graphics g(s);
    SetWindowIcon(LoadImage("icon.png"));

    while (!WindowShouldClose()) {
        g.draw();
        s.simulate();
    }
    CloseWindow();
}
