#pragma once

#include <string>
#include "raylib.h"
#include "Hitbox.h"

class Meta
{
private:

    Texture2D textura;
    float escala;
    Vector2 posicion;

    Hitbox hitbox;

public:

    Meta(const std::string& rutaTextura, Vector2 posicion, float escala);

    ~Meta();

    void Dibujar();
    void Actualizar();
    bool Colisiona(const Hitbox& objeto) const;

    Vector2 GetPosicion() const;
    Rectangle GetHitbox() const;
    Hitbox& GetHitboxObj();
};
