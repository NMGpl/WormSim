#include "Graphics.h"
#include "Simulation.h"
#include "raylib.h"
#include <ctime>

int main(){
    srand(time(0));
    Simulation simulation;
    Graphics g;
    //simulation.setup();

    

    // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
    // SearchAndSetResourceDir("resources");

    while (!WindowShouldClose()) {
        // simulation.step();
        // system("pause");
        // system("cls");
        g.begin();
        g.draw();
        // Setup the back buffer for drawing (clear color and depth buffers)
        //ClearBackground(BLACK);

        // draw some text using the default font
        

        // draw our texture to the screen
        // DrawTexture(wabbit, 400, 200, WHITE);

        g.end();
    }

    // cleanup
    // unload our texture so it can be cleaned up
    // UnloadTexture(wabbit);

    // destroy the window and cleanup the OpenGL context
    CloseWindow();
    return 0;
}