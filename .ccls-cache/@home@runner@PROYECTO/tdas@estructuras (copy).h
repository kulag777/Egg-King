#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "extra.h"
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
    List *inventario;
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
    int valor;
    int x;
    int y;
} Huevo;



typedef struct {
    int id;
    char nombre[50];
    int efecto;//efecto que recupera vida o aumenta daño
} Pocion;

typedef struct {
    int id;
    char nombre[50];
    int efecto;//efecto que aumenta dano
} Espada;

typedef struct {
    int id;
    char nombre[50];
    int efecto;//efecto que aumenta vida maxima
} Armadura;

typedef struct{
    int id;
    char nombre[50];
    int efecto;//efecto aumenta vida y dano pero en menor medida
} Escudo;
