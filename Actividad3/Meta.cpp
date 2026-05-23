#include "Meta.h"

using namespace std;

Meta::Meta(const string& rutaTextura, Vector2 posicion, float escala): 
    posicion(posicion),
    escala(escala)
{
    textura = LoadTexture(rutaTextura.c_str());
    SetTextureFilter(textura, TEXTURE_FILTER_POINT);

    float ancho = textura.width * escala;
    float alto = textura.height * escala;

    hitbox = Hitbox(
        ancho,
        alto,
        { 0,0 },
        false
    );
}

Meta::~Meta()
{
    UnloadTexture(textura);
}

void Meta::Dibujar()
{
    DrawTextureEx(
        textura,
        posicion,
        0.0f,
        escala,
        WHITE
    );

    //debug
    hitbox.Draw();
}

void Meta::Actualizar()
{
    hitbox.Sincro(posicion);
}

bool Meta::Colisiona(const Hitbox& objeto) const
{
    return hitbox.Intersectan(objeto);
}

Vector2 Meta::GetPosicion() const
{
    return posicion;
}

Rectangle Meta::GetHitbox() const
{
    return hitbox.Getbox();
}

Hitbox& Meta::GetHitboxObj()
{
    return hitbox;
}