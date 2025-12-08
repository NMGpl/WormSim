#include "Graphics.h"
#include "Simulation.h"
#include "raylib.h"
#include <chrono>
#include <ctime>

int main(){
    srand(time(0));
    Simulation simulation;
    Graphics g(simulation);
    Image image = LoadImage("icon.png");
    SetWindowIcon(image);
    auto lastTick = std::chrono::high_resolution_clock::now();
    long long tickTime;
    
    while (!WindowShouldClose()) {
        g.begin();
        g.draw();
        g.end();

        tickTime = simulation.getSimSpeed();
        auto now = std::chrono::high_resolution_clock::now();
        if (tickTime != 0 && now - lastTick >= std::chrono::nanoseconds(tickTime)) {
            simulation.simulate();
            lastTick += std::chrono::nanoseconds(tickTime);
        } else if(tickTime == 0) {
            lastTick = std::chrono::high_resolution_clock::now();
        }
		
    }
    // destroy the window and cleanup the OpenGL context
    CloseWindow();
}