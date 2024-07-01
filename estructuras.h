#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/cola.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

typedef struct {
    int id;
    int vida;
    int x, y;
    int DanoBase;
    int experiencia;
    int nivel;
    Queue *inventario;
    List *habilidades;
    char nombre[50];
} Personaje;

// Estructura del enemigo
typedef struct {
    int id;
    int vida;
    int x, y;
} Enemigo;

typedef struct {
    int id;
    char nombre[50];
    char efecto[50];
    int efectoValor;
} Habilidad;

typedef struct {
    int id;
    char nombre[50];
    int efecto;//efecto que aumenta o disminuye dependiendo de que sea
} Objeto;

