#include "Plataforma.h"

using namespace std;

Plataforma::Plataforma(const string& rutaTextura, float escala, Vector2 posicion, float anchoCustom) :
	escala(escala), posicion(posicion), anchoCustom(anchoCustom)
{
	textura = LoadTexture(rutaTextura.c_str());
	SetTextureFilter(textura, TEXTURE_FILTER_POINT);

    float ancho;

    if (anchoCustom > 0) {
        ancho = anchoCustom;
    } else ancho = textura.width * escala;
	
	float alto = textura.height * escala;

	hitbox = Hitbox(ancho, alto, { 0, 0 }, false);
};

Plataforma::~Plataforma() {
	UnloadTexture(textura);
}

void Plataforma::Dibujar() {

	DrawTextureEx(textura,posicion, 0.0f, escala, WHITE);	//con DrawTextureEx controlo escala y rotacion

	//hitbox.Draw();
}

void Plataforma::DibujarTiled()
{
    float anchoTile = textura.width * escala;

    int cantidadTiles =
        (anchoCustom / anchoTile) + 1;

    for (int i = 0; i < cantidadTiles; i++)
    {
        Vector2 pos = {
            posicion.x + (anchoTile * i),
            posicion.y
        };

        DrawTextureEx(
            textura,
            pos,
            0.0f,
            escala,
            WHITE
        );
    }
}

void Plataforma::Actualizar() {

	hitbox.Sincro(posicion);

}