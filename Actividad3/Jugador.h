#pragma once
#pragma once
#include "raylib.h"
#include <string>

using namespace std;

class Jugador {

private:


	Texture2D textura; //imagen que se va a mostrar
	float escala;
	float rotacion;
	bool direccion; //para donde mira: true = derecha - false = izquierda

	//atributos para control de movimiento
	Vector2 posicion;
	float velocidad;

	//atributos para controlar el salto
	bool saltando;
	bool subiendo;
	float alturaSalto;
	float velocidadSalto;
	float pisoY;


public:

	//constructor
	Jugador(const string rutaTextura, Vector2 pos,
		float escala = 1.0f, float rotacion = 0.0f,
		float vel = 3.0f, bool direccion = true,
		bool saltando = false, bool subiendo = false,
		float alturaSalto = 100.0f, float velocidadSalto = 7.0f, float pisoY = 450.0f);


	//destructor
	~Jugador();

	void Dibujar();	//render de la imagen

	void Mover(float x, float y);

	//trabajan en conjunto para 1) ver si esta saltando 2) saltar propiamente
	void Salto();
	void Saltar();

	void SetPosicion(Vector2 pos);

	//controlador principal de movimiento
	//movimiento con flecjhas derecha e izquierda - salto con barra de espacio - reiinicio de posicion con R
	void ActualizarPos();

	Vector2 GetPosicion() const; //devuelve la posicion actual de la imagen
};