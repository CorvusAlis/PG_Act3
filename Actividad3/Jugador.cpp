#include "Jugador.h"

using namespace std;

Jugador::Jugador(const string rutaTextura, Vector2 pos, float escala, float rotacion, float vel, bool direccion, bool saltando, bool subiendo, float alturaSalto, float velocidadSalto, float pisoY)
    : posicion(pos),
    escala(escala),
    rotacion(rotacion),
    velocidad(vel),
    direccion(direccion),
    saltando(saltando),
    subiendo(subiendo),
    alturaSalto(alturaSalto),
    velocidadSalto(velocidadSalto),    //que "tan rapido" sube o baja - cuantos pixeles incrementa o decrementa en Y por unidad de tiempo
    pisoY(pisoY)
{
    //carga de ruta de textura y filtro
    textura = LoadTexture(rutaTextura.c_str());
    SetTextureFilter(textura, TEXTURE_FILTER_POINT);    //este filtro para pixelart
}

Jugador::~Jugador()
{
    UnloadTexture(textura);
}

//render de Jugador 
void Jugador::Dibujar()
{
    //dibuja todo el ancho y alto de la imagen "textura" (el sprite) y lo renderiza desde el pixel 0,0
    //crea un cuadrado con el tamaño del sprite
    Rectangle frisky = { 0, 0, (float)textura.width, (float)textura.height };

    //controlo para donde esta mirando, e invierte el ancho del rectángulo fuente (frisky), la imagen queda "espejada", segun a donde mire
    if (!direccion)
        frisky.width = -frisky.width;

    //controlo la posicion en pantalla
    Rectangle dest = { posicion.x, posicion.y, textura.width * escala, textura.height * escala };
    Vector2 origen = { 0, 0 }; //usa 0,0 del sprite para rotarlo

    //con WHITE en Color se muestra el color original de la imagen
    DrawTexturePro(textura, frisky, dest, origen, rotacion, WHITE);
}

void Jugador::Mover(float x, float y)
{
    posicion.x += x;
    posicion.y += y;
}

void Jugador::ActualizarPos() {

    //salto con barra espaciadora
    if (IsKeyPressed(KEY_SPACE) && !saltando) Saltar(); //trigger del salto
    Salto();    //accion efectiva del salto

    //movimiento con las flechas del teclado
    if (IsKeyDown(KEY_RIGHT)) {
        Mover(velocidad, 0);
        direccion = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
        Mover(-velocidad, 0);
        direccion = false;
    }

}

void Jugador::Saltar() {

    //control para evitar spam de salto
    //mientras este en medio del salto, apretar el espacio no hace que salte nuevamente
    if (!saltando) {
        saltando = true;
        subiendo = true;
    }
}

void Jugador::Salto() {

    if (!saltando) return;  //si no esta saltando, vuelve

    if (saltando) {
        if (subiendo) {

            //velocidad del salto - que tantos pixeles "sube" por unidad de tiempo
            posicion.y -= velocidadSalto;

            //pisoY - alturaSalto = controlo la "altura" del salto - con los valores fijos actuales "salta" hasta y=420
            if (posicion.y <= pisoY - alturaSalto)
                subiendo = false;   //si llego al limite indicado por la altura del salto, termino de subir
        }

        else {
            //si ya llego al limite, subiendo = false (cambia el control del segundo if)
            //ahora se suma la posicion actual y la velocidad para moverlo hacia abajo
            posicion.y += velocidadSalto;

            if (posicion.y >= pisoY) { //es decir, si ya llego al piso
                posicion.y = pisoY; //evita que el Jugador se hunda en el piso - el final del salto lo coloca en y = 500 sin importar la suma de velocidadSalto (basicamente es un control de colision con el piso)
                saltando = false;   //ya no esta saltando, puede volver a saltar
            }
        }
    }
}

void Jugador::SetPosicion(Vector2 pos)
{
    posicion = pos;
}

Vector2 Jugador::GetPosicion() const
{
    return posicion;
}