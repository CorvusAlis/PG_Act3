#pragma once

#include <list>
#include <vector>

#include "Vagon.h"
#include "Plataforma.h"
#include "Meta.h"
#include "OperacionAritmetica.h"

//(al fin implemento un gamemanager)
//encapsulkamiento en clase Juego de las responsabilidades del gameplay
//para dejar limpio el main

enum EstadoJuego
{
    JUGANDO,
    RESOLVIENDO,
    VICTORIA,
    DERROTA
};

class Juego
{
private:

    //lista para manejar el tren (locomotora + vagones recolectados)
    list<Vagon*> tren;

    //vagones sueltos
    vector<Vagon*> vagonesMapa;
    vector<Vector2> historialPosiciones;

    vector<Plataforma*> plataformas;

    Meta* meta;
    Vagon* vagonActual;
    Vagon* vagonPendiente;  //para determinar que se hace con el vagon que se esta resolviendo

    OperacionAritmetica* operacionActual;

    Texture2D background;

    float velocidadTren;
    float alturaPiso;
    int pisoActual;
    bool preguntaActiva;

    EstadoJuego estadoActual;

public:

    Juego();
    ~Juego();

    void Actualizar();
    void Dibujar();

private:

    void InicializarPisos();
    void InicializarTren();
    void InicializarVagonesMapa();
    void InicializarMeta();

    void InsertarVagonOrdenado(Vagon* nuevo);

    void VerificarDerrota();
    void VerificarVictoria();

    void DetectarColisiones();

    void ReiniciarHistorial();

    void MoverTren();
};
