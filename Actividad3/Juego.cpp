#include "Juego.h"

using namespace std;

const int ANCHO_PANTALLA = 1600;
const int ALTO_PANTALLA = 900;
const float ESCALA_TREN = 1.0f;
const float VELOCIDAD_TREN = 2.5f;
const float DISTANCIA_VAGONES = 50; //guarda los frames de retraso para el movimiento
const int CANTIDAD_PISOS = 3;
const float ESCALA_PISO = 0.75f;

Juego::Juego()
{
    estadoActual = JUGANDO;

    background = LoadTexture("assets/background.png");

    velocidadTren = VELOCIDAD_TREN;
    alturaPiso = 250.0f;
    pisoActual = 0;

    operacionActual = nullptr;
    vagonPendiente = nullptr;

    InicializarPisos();
    InicializarTren();
    InicializarVagonesMapa();
    InicializarMeta();
}

Juego::~Juego()
{
    for (auto v : tren)
        delete v;

    for (auto p : plataformas)
        delete p;

    for (auto v : vagonesMapa)
        delete v;

    delete meta;
}

void Juego::InicializarPisos()
{
    float y = 180;

    for (int i = 0; i < CANTIDAD_PISOS; i++)
    {
        plataformas.push_back(

            new Plataforma(
                "assets/plataforma.png",
                ESCALA_PISO,
                { 0, y },
                GetScreenWidth()
            )
        );

        y += alturaPiso;
    }
}

//tren inicial con locomotora y dos vagones
void Juego::InicializarTren()
{
    //el primer "vagon" es la locomotora - siempre se inicializa
    Vagon* locomotora = new Vagon(
        "assets/locomotora.png",
        { 0, 110 },
        ESCALA_TREN,
        true
    );

    tren.push_back(locomotora);

    //el primer y segundo vagon tambien comienzan inicializados
    Vagon* v1 = new Vagon(
        "assets/vagon.png",
        { 50 -DISTANCIA_VAGONES, 110 },
        ESCALA_TREN,
        false,
        3
    );

    tren.push_back(v1);

    Vagon* v2 = new Vagon(
        "assets/vagon.png",
        { 50 -DISTANCIA_VAGONES * 2 , 110 },
        ESCALA_TREN,
        false,
        7
    );

    v1->MostrarNumero(true);
    v2->MostrarNumero(true);

    tren.push_back(v2);

    //para corregir el snap visual de los vagones al moverse por primera vez
    //dejo un historial previo con posiciones ya cargadas para que aparezcan moviendose desde fuera de la pantalla
    Vector2 posInicial = locomotora->GetPosicion();

    int cantidadHistorial =
        tren.size() * DISTANCIA_VAGONES;

    for (int i = 0; i < cantidadHistorial; i++)
    {
        historialPosiciones.push_back(
            {
                posInicial.x - (i * velocidadTren),
                posInicial.y
            }
        );
    }
}

void Juego::InicializarMeta()
{
    meta = new Meta(
        "assets/meta.png",
        { ANCHO_PANTALLA - 150, 600 },
        2.0f
    );
}

//vagones a recoger puestos en el mapa
void Juego::InicializarVagonesMapa()
{
    //primer piso
    vagonesMapa.push_back(

        new Vagon(
            "assets/vagon.png",
            { 600, 110 },
            ESCALA_TREN,
            false,
            5
        )
    );

    vagonesMapa.push_back(

        new Vagon(
            "assets/vagon.png",
            { 1200, 110 },
            ESCALA_TREN,
            false,
            2
        )
    );

    //segundo piso
    vagonesMapa.push_back(

        new Vagon(
            "assets/vagon.png",
            { 250, 360 },
            ESCALA_TREN,
            false,
            8
        )
    );

    vagonesMapa.push_back(

        new Vagon(
            "assets/vagon.png",
            { 750, 360 },
            ESCALA_TREN,
            false,
            8
        )
    );

    vagonesMapa.push_back(

        new Vagon(
            "assets/vagon.png",
            { 1350, 360 },
            ESCALA_TREN,
            false,
            4
        )
    );

    //tercer piso
    vagonesMapa.push_back(

        new Vagon(
            "assets/vagon.png",
            { 300, 610 },
            ESCALA_TREN,
            false,
            6
        )
    );

    vagonesMapa.push_back(

        new Vagon(
            "assets/vagon.png",
            { 950, 610 },
            ESCALA_TREN,
            false,
            6
        )
    );
}

void Juego::Actualizar()
{
    switch (estadoActual)
    {
    case JUGANDO:

        MoverTren();

        for (auto v : tren)
            v->Actualizar();

        for (auto p : plataformas)
            p->Actualizar();

        for (auto v : vagonesMapa)
            v->Actualizar();

        meta->Actualizar();

        DetectarColisiones();

        VerificarVictoria();
        VerificarDerrota();

        break;

    case RESOLVIENDO:

        operacionActual->Actualizar();

        //si la operacion termino
        if (operacionActual->Terminada())
        {
            //si respondio correctamente
            if (operacionActual->Correcta())
            {
                vagonPendiente->SetResultado(
                    operacionActual->GetResultado()
                );

                vagonPendiente->MostrarNumero(true);    //muestra el resultado al engancharse al tren

                InsertarVagonOrdenado(vagonPendiente);  //coloca el vagon resuelto ordenado de menor a mayor
            }

            //si respondio incorrectamente
            else
            {
                //para no eliminar la locomotora
                if (tren.size() > 1)
                {
                    delete tren.back();
                    tren.pop_back();
                    VerificarDerrota();
                }
            }

            //limpieza para proximo vagon
            delete operacionActual;

            operacionActual = nullptr;
            vagonPendiente = nullptr;

            //vuelvo al estado JUGANDO
            estadoActual = JUGANDO;
        }

        break;
    }
}

void Juego::Dibujar()
{

    Rectangle source = {
        0,
        0,
        (float)background.width,
        (float)background.height
    };

    Rectangle dest = {
        0,
        0,
        (float)ANCHO_PANTALLA,
        (float)ALTO_PANTALLA
    };

    DrawTexturePro(
        background,
        source,
        dest,
        { 0,0 },
        0.0f,
        WHITE
    );

    for (auto p : plataformas)
        p->DibujarTiled();

    meta->Dibujar();

    for (auto v : tren)
        v->Dibujar();

    for (auto v : vagonesMapa)
        v->Dibujar();

    if (estadoActual == RESOLVIENDO)
    {
        //el nivel queda sombreado
        DrawRectangle(
            0,
            0,
            ANCHO_PANTALLA,
            ALTO_PANTALLA,
            Fade(BLACK, 0.7f)
        );

        operacionActual->Dibujar();
    }

    if (estadoActual == VICTORIA)
    {
        DrawRectangle(
            0,
            0,
            ANCHO_PANTALLA,
            ALTO_PANTALLA,
            Fade(BLACK, 0.7f)
        );

        DrawText(
            "GANASTE!",
            600,
            300,
            60,
            GREEN
        );
    }

    if (estadoActual == DERROTA)
    {
        DrawRectangle(
            0,
            0,
            ANCHO_PANTALLA,
            ALTO_PANTALLA,
            Fade(BLACK, 0.7f)
        );

        DrawText(
            "PERDISTE!",
            600,
            300,
            60,
            RED
        );
    }
}

//uso de historial de posiciones de vagones para simular el movimiento del tren completo (queda tipo Snake clasico)
void Juego::MoverTren()
{
    auto locomotora = tren.front();

    //mueve locomotora
    locomotora->Mover(velocidadTren, 0);

    //guarda posicion actual
    historialPosiciones.insert(
        historialPosiciones.begin(),
        locomotora->GetPosicion()
    );

    //limite tamaño historial
    int maxHistorial =
        tren.size() * DISTANCIA_VAGONES;

    if (historialPosiciones.size() > maxHistorial)
    {
        historialPosiciones.pop_back();
    }

    //mueve vagones
    int i = 1;

    for (auto it = ++tren.begin();
        it != tren.end();
        ++it)
    {
        int indice =
            i * DISTANCIA_VAGONES;

        if (indice < historialPosiciones.size())
        {
            (*it)->SetPosicion(
                historialPosiciones[indice]
            );
        }

        i++;
    }

    auto ultimo = tren.back();

    //pasa al proximo piso cuando el ultimo vagon sale completo de la pantalla
    if (ultimo->GetPosicion().x > ANCHO_PANTALLA)
    {
        if (pisoActual >= CANTIDAD_PISOS - 1)
            return; //para que no siga bajando indefinidamente

        pisoActual++;

        auto locomotora = tren.front();

        float nuevoY =
            110 + (pisoActual * alturaPiso);

        locomotora->SetPosicion(
            { 50, nuevoY }
        );

        ReiniciarHistorial();
    }
}

void Juego::DetectarColisiones()
{
    auto locomotora = tren.front();

    for (auto it = vagonesMapa.begin();
        it != vagonesMapa.end();)
    {
        Vagon* vagon = *it;

        if (locomotora->GetHitboxObj().Intersectan(
            vagon->GetHitboxObj()))
        {
            //si colisiona locomotora-vagon se guarda el vagon como pendiente y se crea una nueva suma
            vagonPendiente = vagon;

            operacionActual = new OperacionAritmetica(
                5.0f,
                { 650, 350 }
            );

            //eliminar del mapa
            it = vagonesMapa.erase(it); //no borra el objeto vagon, lo elimina del vector de mapas

            //paso al estado RESOLVIENDO
            estadoActual = RESOLVIENDO;

            return;
        }

        else
        {
            ++it;
        }
    }
}

void Juego::InsertarVagonOrdenado(Vagon* nuevo)
{
    //iterador al primer vagon despues de locomotora
    auto it = ++tren.begin();

    //buscar posicion correcta
    while (it != tren.end())
    {
        if (nuevo->GetResultado() <
            (*it)->GetResultado())
        {
            break;
        }

        ++it;
    }

    //insertar antes del elemento encontrado
    tren.insert(it, nuevo);

    //reconstruir historial visual
    ReiniciarHistorial();
}

void Juego::VerificarDerrota()
{
    if (tren.size() <= 1)   //solo queda la locomotora
    {
        estadoActual = DERROTA;
    }
}

void Juego::VerificarVictoria()
{
    auto locomotora = tren.front();

    if (locomotora->GetHitboxObj().Intersectan(
        meta->GetHitboxObj()))
    {
        if (tren.size() > 1)
        {
            estadoActual = VICTORIA;
        }
    }
}


void Juego::ReiniciarHistorial()
{
    historialPosiciones.clear();

    auto locomotora = tren.front();

    Vector2 posInicial =
        locomotora->GetPosicion();

    int cantidadHistorial =
        tren.size() * DISTANCIA_VAGONES;

    for (int i = 0; i < cantidadHistorial; i++)
    {
        historialPosiciones.push_back(
            {
                posInicial.x - (i * velocidadTren),
                posInicial.y
            }
        );
    }
}