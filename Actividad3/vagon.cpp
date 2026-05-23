#include "Vagon.h"

using namespace std;

Vagon::Vagon(const string& rutaTextura,  Vector2 posicion,  float escala, bool locomotora, int resultado, float rotacion): 
    posicion(posicion),
    escala(escala),
    locomotora(locomotora),
    resultado(resultado),
    rotacion(rotacion)
{

    textura = LoadTexture(rutaTextura.c_str());
    SetTextureFilter(textura, TEXTURE_FILTER_POINT);

    float ancho = textura.width * escala;
    float alto = textura.height * escala;

    hitbox = Hitbox(
        ancho,
        alto,
        { 0, 0 },
        false
    );

    mostrarNumero = false;
}

Vagon::~Vagon() {
    UnloadTexture(textura);
}

void Vagon::Dibujar()
{
    Rectangle source = {
        0,
        0,
        (float)textura.width,
        (float)textura.height
    };

    Rectangle dest = {
        posicion.x,
        posicion.y,
        textura.width * escala,
        textura.height * escala
    };

    Vector2 origen = { 0, 0 };

    DrawTexturePro(
        textura,
        source,
        dest,
        origen,
        rotacion,
        WHITE
    );

    //

    //dibujar valor del vagon
    if (mostrarNumero)
    {
        string texto =
            to_string(resultado);

        int fontSize = 30;

        int anchoTexto =
            MeasureText(
                texto.c_str(),
                fontSize
            );

        float xTexto =
            posicion.x +
            (dest.width / 2) -
            (anchoTexto / 2);

        float yTexto =
            posicion.y +
            (dest.height / 2) -
            (fontSize / 2);

        DrawText(
            texto.c_str(),
            (int)xTexto,
            (int)yTexto,
            fontSize,
            RAYWHITE
        );
    }

    //debug hitbox
    hitbox.DebugOn(false);
    hitbox.Draw();
}

void Vagon::Actualizar()
{
    hitbox.Sincro(posicion);
}

void Vagon::Mover(float x, float y)
{
    posicion.x += x;
    posicion.y += y;
}

bool Vagon::EsLocomotora() const
{
    return locomotora;
}

//getters y setters

void Vagon::MostrarNumero(bool estado)
{
    mostrarNumero = estado;
}

void Vagon::SetPosicion(Vector2 pos)
{
    posicion = pos;
}

void Vagon::SetResultado(int valor)
{
    resultado = valor;
}

Vector2 Vagon::GetPosicion() const
{
    return posicion;
}

int Vagon::GetResultado() const
{
    return resultado;
}

Rectangle Vagon::GetHitbox() const
{
    return hitbox.Getbox();
}

Hitbox& Vagon::GetHitboxObj()
{
    return hitbox;
}