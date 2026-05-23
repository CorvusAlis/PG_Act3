#include "raylib.h"
#include <string>
#include <ctime>

#include "Juego.h"  //manager

int main() {

    InitWindow(1600, 900, "Actividad 3");
    SetTargetFPS(60);

    Juego juego;

    srand(time(nullptr));

    while (!WindowShouldClose())
    {
        ClearBackground(DARKBLUE);

        //UPDATES
        juego.Actualizar();

        //RENDERS
        BeginDrawing();

        juego.Dibujar();

        EndDrawing();
    }

    return 0;
}