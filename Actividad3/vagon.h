#pragma once

#include <string>
#include "raylib.h"
#include "Hitbox.h"

class Vagon
{
private:

    Texture2D textura;

    Vector2 posicion;

    float escala;
    float rotacion;

    bool locomotora;

    int resultado;
    bool mostrarNumero;

    Hitbox hitbox;

public:

    Vagon(const std::string& rutaTextura, Vector2 posicion, float escala, bool locomotora, int resultado = 0, float rotacion = 0.0f);

    ~Vagon();

    void Dibujar();
    void Actualizar();
    void Mover(float x, float y);

    bool EsLocomotora() const;

    void SetPosicion(Vector2 pos);
    void SetResultado(int valor);
    void MostrarNumero(bool estado);

    Vector2 GetPosicion() const;
    int GetResultado() const;
    Rectangle GetHitbox() const;
    Hitbox& GetHitboxObj();

};