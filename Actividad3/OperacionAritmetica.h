#pragma once
#include <string>
#include "raylib.h"

using namespace std;

class OperacionAritmetica
{
private:

    int a, b, c, resultado;

    string respuestaUsuario;

    bool activa;
    bool respondida;
    bool correcta;

    float tiempoLimite;
    float tiempoActual;

    Vector2 posicionTexto;

public:

    OperacionAritmetica(float tiempoLimite, Vector2 posicionTexto);

    void Generar();
    void Actualizar();
    void Dibujar();
    bool RespuestaCorrecta() const;
    bool Terminada() const;
    bool Correcta() const;

    int GetResultado() const;

    void Reiniciar();
};
