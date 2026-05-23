#pragma once
#include "raylib.h"
#include "Hitbox.h"
#include <string>

using namespace std;

class Plataforma {

private:
	Texture2D textura;
	float escala;
	Vector2 posicion;
	float anchoCustom;

	Hitbox hitbox;

public:

	Plataforma(const string& rutaTextura, float escala, Vector2 posicion, float anchoCustom = 0.0f);
	~Plataforma();

	void Dibujar();
	void DibujarTiled();
	void Actualizar();

	const Hitbox& GetHitbox() const { return hitbox; }
	Vector2 GetPosicion() const { return posicion; }
	float GetTop() const { return posicion.y; }
	float GetAncho() const { return hitbox.Getbox().width; }
};