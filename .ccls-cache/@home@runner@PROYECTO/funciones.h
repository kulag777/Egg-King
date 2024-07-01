#ifndef funciones_h
#define funciones_h
#include "estructuras.h"
#define MAX 30

void aplicarDefensaSolida(Personaje *jugador, int aumentoVidaMax);

void aplicarRegeneracion(Personaje *jugador, int regeneracion);

void aplicarFuerzaBruta(Personaje *jugador, int aumentoDanio);

void exportarHabilidades(Personaje *jugador);

void exportarVida(int vida);

void menuMuerte(Personaje *jugador);

void setNonBlockingMode(int enable);

void limpiarBufferEntrada();

void actualizarCSV(int seleccionada);

void actualizarMenuActualCSV(int menuID);

int elegirOpcion(int opciones, int menuID);

void mostrarHabilidades(Personaje *jugador);

void mostrarMenu();

Personaje elegirPersonaje();

void inicializarMapa(int mapa[MAX][MAX]);

void moverPersonaje(Personaje *jugador, int mapa[MAX][MAX], char direccion);

int randRange(int min, int max);

void generarEnemigos(Enemigo *enemigos, int numEnemigos, Personaje *jugador, int mapa[MAX][MAX]);

void moverEnemigos(Enemigo *enemigos, int numEnemigos, Personaje *jugador, int mapa[MAX][MAX]);

void exportarDatos(int mapa[MAX][MAX], Personaje *jugador);

void aplicarEfectoObjeto(Personaje *jugador, int tipoObjeto, int efecto);

void elegirObjeto(Personaje *jugador);

#endif