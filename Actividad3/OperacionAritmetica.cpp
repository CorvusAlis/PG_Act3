#include "OperacionAritmetica.h"

using namespace std;

OperacionAritmetica::OperacionAritmetica(float tiempoLimite, Vector2 posicionTexto): 
    tiempoLimite(tiempoLimite),
    posicionTexto(posicionTexto)
{
    a = 0;
    b = 0;
    c = 0;

    resultado = 0;

    respuestaUsuario = "";

    activa = false;
    respondida = false;
    correcta = false;

    tiempoActual = tiempoLimite;

    Generar();
}

void OperacionAritmetica::Generar()
{
    a = rand() % 10;
    b = rand() % 10;
    c = rand() % 10;

    resultado = a + b + c;

    respuestaUsuario = "";

    activa = true;
    respondida = false;
    correcta = false;

    tiempoActual = tiempoLimite;
}

void OperacionAritmetica::Actualizar()
{
    if (!activa || respondida)
        return;

    // Actualiza timer
    tiempoActual -= GetFrameTime();

    // Si se acaba el tiempo
    if (tiempoActual <= 0)
    {
        tiempoActual = 0;

        respondida = true;
        correcta = false;

        return;
    }

    //input numerico
    int key = GetCharPressed();

    while (key > 0)
    {
        if (key >= '0' && key <= '9')
        {
            respuestaUsuario += (char)key;
        }

        key = GetCharPressed();
    }

    //borrar numero
    if (IsKeyPressed(KEY_BACKSPACE) &&
        !respuestaUsuario.empty())
    {
        respuestaUsuario.pop_back();
    }


    //confirmar respuesta con enter
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))
    {
        int respuesta = 0;

        if (!respuestaUsuario.empty())
        {
            respuesta = stoi(respuestaUsuario); //stoi: funcion que convierte un string a un int
        }

        correcta = (respuesta == resultado);

        respondida = true;
    }
}

void OperacionAritmetica::Dibujar()
{
    if (!activa)
        return;

    //render operacion
    string textoOperacion =
        to_string(a) + " + " +
        to_string(b) + " + " +
        to_string(c) + " = ?";

    DrawText(
        textoOperacion.c_str(),
        posicionTexto.x,
        posicionTexto.y,
        30,
        WHITE
    );

    //render respuesta
    string textoRespuesta =
        "Respuesta: " + respuestaUsuario;

    DrawText(
        textoRespuesta.c_str(),
        posicionTexto.x,
        posicionTexto.y + 40,
        25,
        YELLOW
    );

    //timer
    string textoTiempo =
        "Tiempo: " + to_string((int)tiempoActual);

    DrawText(
        textoTiempo.c_str(),
        posicionTexto.x,
        posicionTexto.y + 80,
        25,
        RED
    );
}

bool OperacionAritmetica::RespuestaCorrecta() const
{
    return correcta;
}

bool OperacionAritmetica::Terminada() const
{
    return respondida;
}

bool OperacionAritmetica::Correcta() const
{
    return correcta;
}

int OperacionAritmetica::GetResultado() const
{
    return resultado;
}

void OperacionAritmetica::Reiniciar()
{
    activa = false;

    respondida = false;
    correcta = false;

    respuestaUsuario = "";

    tiempoActual = tiempoLimite;
}