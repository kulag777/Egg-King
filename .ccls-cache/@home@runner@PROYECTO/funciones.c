#include "estructuras.h"
#include "tdas/cola.h"
#include "tdas/extra.h"
#include "tdas/list.h"
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define MAX 30


void aplicarDefensaSolida(Personaje *jugador, int aumentoVidaMax) {
  jugador->vida += aumentoVidaMax;
  jugador->vida = jugador->vida; // Restaurar vida al nuevo máximo
  printf("Habilidad 'Defensa sólida' aplicada. Tu vida máxima ahora es %d.\n", jugador->vida);
}

void aplicarRegeneracion(Personaje *jugador, int regeneracion) {
  // Esta función debe ser llamada en cada turno del juego para aplicar la regeneración
  jugador->vida += regeneracion;
  if (jugador->vida > 100) {
    jugador->vida = jugador->vida; // No permitir que la vida exceda el máximo
  }
  printf("Habilidad 'Regeneración' aplicada. Tu vida ahora es %d.\n", jugador->vida);
}

void aplicarFuerzaBruta(Personaje *jugador, int aumentoDanio) {
  jugador->DanoBase += aumentoDanio;
  printf("Habilidad 'Fuerza bruta' aplicada. Tu daño base ahora es %d.\n", jugador->DanoBase);
}

// Función para importar los objetos del jugador desde un archivo CSV
void exportarHabilidades(Personaje *jugador) {
  FILE *archivo = fopen("Python/habilidades.csv", "w");
  if (!archivo) {
    perror("No se pudo abrir el archivo habilidades.csv");
    return;
  }

  fprintf(archivo, "Nombre,Descripción\n");

  for (int i = 0; i < list_size(jugador->habilidades); i++) {
    Habilidad *habilidad = (Habilidad *)list_get(jugador->habilidades, i);
    fprintf(archivo, "%s,%s\n", habilidad->nombre, habilidad->efecto);
  }

  fclose(archivo);
}

void exportarVida(int vida)
{
  FILE *archivo = fopen("Python/vida.csv", "w");
  if (archivo == NULL) {
    perror("No se pudo abrir el archivo vida.csv");
    return;
  }
  fprintf(archivo, "%i\n", vida);
  fclose(archivo);
}


// Función para importar los objetos del jugador desde un archivo CSV
void menuMuerte(Personaje *jugador) {
  FILE *archivo = fopen("Python/menuMuerte.csv", "w");
  if (!archivo) {
    perror("No se pudo abrir el archivo menuMuerte.csv");
    return;
  }
  fprintf(archivo, "Experiencia obtenida\n%i\n", jugador->experiencia);
  fprintf(archivo, "Enemigos Muertos\n%i\n", (jugador->experiencia) / 2);
  fclose(archivo);
}
// Función para cambiar el modo del terminal a no bloqueante
void setNonBlockingMode(int enable) {
  struct termios ttystate;
  int fd = fileno(stdin);

  tcgetattr(fd, &ttystate);

  if (enable) {
    ttystate.c_lflag &= ~ICANON; // Deshabilitar modo canónico
    ttystate.c_lflag &= ~ECHO;   // No mostrar entrada en pantalla
    ttystate.c_cc[VMIN] = 1;     // Leer un carácter a la vez
  } else {
    ttystate.c_lflag |= ICANON; // Habilitar modo canónico
    ttystate.c_lflag |= ECHO;   // Mostrar entrada en pantalla
  }

  tcsetattr(fd, TCSANOW, &ttystate); // Aplicar los cambios inmediatamente
}

// Función para obtener la entrada del usuario sin bloquear el programa
void limpiarBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Función para registrar la entrada del usuario
void actualizarCSV(int seleccionada) {
  FILE *archivo = fopen("Python/registro_menu.csv", "w");
  if (archivo == NULL) {
    printf("Error al abrir el archivo de registro del menú.");
    return;
  }

  fprintf(archivo, "%d\n", seleccionada);

  fclose(archivo);
}

// Función para prinetar el menú en donde el usuario se encuentra para poder mostrarlo en el codigo de python
void actualizarMenuActualCSV(int menuID) {
  FILE *archivo = fopen("Python/menuActual.csv", "w");
  if (archivo == NULL) {
    printf("Error al abrir el archivo de menú actual.");
    return;
  }

  fprintf(archivo, "%d\n", menuID);
  fclose(archivo);
}

// Función para elegir una opción del menú
int elegirOpcion(int opciones, int menuID) 
{
    int seleccionada = 0;
    actualizarCSV(seleccionada);
    actualizarMenuActualCSV(menuID);

    while (1) {
        printf("\nIngrese una opción (1-%d): ", opciones);
        if (scanf("%d", &seleccionada) != 1) {
            limpiarBufferEntrada(); // Limpiar el buffer en caso de entrada no válida
            printf("Entrada inválida. Por favor, ingrese un número entre 1 y %d.\n", opciones);
            continue;
        }

        // Verificar que la opción ingresada esté dentro del rango válido
        if (seleccionada >= 1 && seleccionada <= opciones) {
            break;
        } else {
            printf("Opción inválida. Por favor, ingrese un número entre 1 y %d.\n", opciones);
        }
    }
    // Actualizar nuevamente para reflejar la opción ingresada
    actualizarCSV(seleccionada);

    return seleccionada; // Restar 1 para devolver la opción en base 0
}

// Función para mostrar las habilidades del jugador
void mostrarHabilidades(Personaje *jugador) {
    exportarHabilidades(jugador);
}

// Función para mostrar el menu principal
void mostrarMenu() {
  printf("Menu Principal:\n");
  printf("1. Nueva partida\n");
  printf("2. Ver objetos\n");
  printf("3. Ver habilidades\n");
  printf("4. Créditos\n");
  printf("5. Ajustes\n");
  printf("6. Salir\n");
}

// Función para elegir un personaje
Personaje elegirPersonaje() {
  Personaje personajes[4] = {
      {7, 100, 0, 0, 10, 0, 1, queue_create(), list_create(), "Kulag"},
      {8, 100, 0, 0, 10, 0, 1, queue_create(), list_create(), "Cris"},
      {9, 100, 0, 0, 10, 0, 1, queue_create(), list_create(), "Gogo"},
      {10, 100, 0, 0, 10, 0, 1, queue_create(), list_create(), "Javi"}};

  printf("Elige tu personaje:\n");
  for (int i = 0; i < 4; i++) {
    printf("%d. %s\n", i + 1, personajes[i].nombre);
  }
  int seleccion = elegirOpcion(4, 2); // Menu de los jugadores
  limpiarBufferEntrada();

  if (seleccion >= 1 && seleccion <= 4) {
    // Guardar el nombre en un archivo CSV
    FILE *archivo = fopen("Python/personajes.csv", "w"); // Abrir el archivo en modo escritura
    if(archivo != NULL){
      fprintf(archivo, "%s\n", personajes[seleccion - 1].nombre); // Escribir el nombre en el archivo
      fclose(archivo); // Cerrar el archivo
    }else
      printf("Error al abrir el archivo para escritura.\n");
    return personajes[seleccion - 1];
  } else {
    printf("Selección inválida. Eligiendo el primer personaje por defecto.\n");
    return personajes[0];
  }
}

void inicializarMapa(int mapa[MAX][MAX]) {
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      mapa[i][j] = 0; // Inicializa el mapa con 0s
    }
  }
}

// Función para mover el personaje
void moverPersonaje(Personaje *jugador, int mapa[MAX][MAX], char direccion) {
  int nueva_x = jugador->x;
  int nueva_y = jugador->y;

  if (direccion == 'w') {
    nueva_x--;
  } else if (direccion == 's') {
    nueva_x++;
  } else if (direccion == 'a') {
    nueva_y--;
  } else if (direccion == 'd') {
    nueva_y++;
  }

  // Verificar los límites del mapa
  if (nueva_x >= 0 && nueva_x < MAX && nueva_y >= 0 && nueva_y < MAX) {
    // Verificar si la próxima posición está ocupada por un muro
    if (mapa[nueva_x][nueva_y] == 0) {
      // Mover al personaje en el mapa
      mapa[jugador->x][jugador->y] = 0; // Limpiar la posición anterior
      jugador->x = nueva_x;
      jugador->y = nueva_y;
      mapa[nueva_x][nueva_y] = jugador->id; // Colocar en la nueva posición
    }
  }
}

// Función para generar un número aleatorio dentro de un rango
int randRange(int min, int max) { return rand() % (max - min + 1) + min; }

// Función para generar enemigos dentro de un rango alrededor del jugador
void generarEnemigos(Enemigo *enemigos, int numEnemigos, Personaje *jugador,
                     int mapa[MAX][MAX]) {
  for (int i = 0; i < numEnemigos; i++) {
    int x, y;
    do {
      x = randRange(0, MAX - 1);
      y = randRange(0, MAX - 1);
    } while (mapa[x][y] != 0 || abs(x - jugador->x) < 2 ||
             abs(y - jugador->y) < 2);

    enemigos[i].id = 1;
    enemigos[i].vida = 25; // Vida inicial de los enemigos
    enemigos[i].x = x;
    enemigos[i].y = y;
    mapa[x][y] = enemigos[i].id; // Colocar en la nueva posición
  }
}

// Función para mover los enemigos hacia el jugador
void moverEnemigos(Enemigo *enemigos, int numEnemigos, Personaje *jugador,
                   int mapa[MAX][MAX]) {
  for (int i = 0; i < numEnemigos; i++) {
    // Limpiar la posición anterior si está dentro de los límites
    if (enemigos[i].x >= 0 && enemigos[i].x < MAX && enemigos[i].y >= 0 &&
        enemigos[i].y < MAX) {
      mapa[enemigos[i].x][enemigos[i].y] = 0;
    }

    int dx = 0, dy = 0;

    // Movimiento en dirección X
    if (enemigos[i].x < jugador->x) {
      dx = 1;
    } else if (enemigos[i].x > jugador->x) {
      dx = -1;
    }

    // Movimiento en dirección Y
    if (enemigos[i].y < jugador->y) {
      dy = 1;
    } else if (enemigos[i].y > jugador->y) {
      dy = -1;
    }
    exportarVida(jugador->vida);
    // Verifica colisión con el jugador
    if (enemigos[i].x + dx == jugador->x && enemigos[i].y + dy == jugador->y) {
      jugador->vida -= 10; // Reducir la vida del jugador
      exportarVida(jugador->vida); //deberia pasarle la vida
      printf("\nEl jugador ha sido atacado por un enemigo! Vida restante: %d\n",
             jugador->vida);
    } else {
      enemigos[i].x += dx;
      enemigos[i].y += dy;
    }

    // Asegura que los enemigos no se muevan fuera del mapa
    if (enemigos[i].x < 0)
      enemigos[i].x = 0;
    if (enemigos[i].x >= MAX)
      enemigos[i].x = MAX - 1;
    if (enemigos[i].y < 0)
      enemigos[i].y = 0;
    if (enemigos[i].y >= MAX)
      enemigos[i].y = MAX - 1;

    // Actualiza la nueva posición si está dentro de los límites y no es la
    // posición del jugador
    if (enemigos[i].x >= 0 && enemigos[i].x < MAX && enemigos[i].y >= 0 &&
        enemigos[i].y < MAX) {
      if (!(enemigos[i].x == jugador->x && enemigos[i].y == jugador->y)) {
        mapa[enemigos[i].x][enemigos[i].y] = enemigos[i].id;
      }
    } else {
      printf("Error: enemigo fuera de los límites del mapa\n");
    }
  }
}

void exportarDatos(int mapa[MAX][MAX], Personaje *jugador) {
  FILE *archivo = fopen("Python/mapa.csv", "w");
  if (archivo == NULL) {
    printf("Error al abrir el archivo.");
    return;
  }

  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      fprintf(archivo, "%d,", mapa[i][j]);
    }
    fprintf(archivo, "\n");
  }

  fclose(archivo);
}

void aplicarEfectoObjeto(Personaje *jugador, int tipoObjeto, int efecto) {
  switch (tipoObjeto) {
  case 1: // Espada
    jugador->DanoBase += efecto;
    printf("Has elegido una espada. Tu fuerza aumentó en %d.\n", efecto);
    break;
  case 2: // Armadura
    jugador->vida += efecto;
    printf("Has elegido una armadura. Tu vida máxima aumentó en %d.\n", efecto);
    break;
  case 3: // Escudo
    jugador->vida += efecto;
    jugador->DanoBase += efecto;
    printf("Has elegido un escudo. Tu vida aumentó en %d y tu fuerza aumentó "
           "en %d.\n",
           efecto, efecto);
    break;
  }
}

void elegirObjeto(Personaje *jugador) {
  //actualizarMenuActualCSV()
  Objeto espadas[3] = {{1, "Espada de Fuego", 10},
                       {2, "Espada de Hielo", 8},
                       {3, "Espada de Trueno", 12}};
  Objeto armaduras[3] = {{1, "Armadura de Dragón", 20},
                         {2, "Armadura de Acero", 15},
                         {3, "Armadura de Diamante", 25}};
  Objeto escudos[3] = {{1, "Escudo de Plata", 5},
                       {2, "Escudo de Oro", 7},
                       {3, "Escudo de Diamante", 10}};

  printf("Elige un tipo de objeto:\n");
  printf("1. Espada\n");
  printf("2. Armadura\n");
  printf("3. Escudo\n");

  int seleccionTipo = elegirOpcion(3, 3); // Menu de los tipos de objetos
  actualizarCSV(seleccionTipo);
  Objeto *nuevoObjeto = (Objeto *)malloc(sizeof(Objeto));
  if (!nuevoObjeto) {
    printf("Error al asignar memoria para el nuevo objeto.\n");
    return;
  }

  switch (seleccionTipo) 
  {
  case 1:
    printf("Elige una espada:\n");
    actualizarMenuActualCSV(4);
    for (int i = 0; i < 3; i++) 
    {
      printf("%d. %s\n", i + 1, espadas[i].nombre);
    }
    int seleccionObjeto = elegirOpcion(3, 4); // Menu de los objetos específicos
    if (seleccionObjeto >= 1 && seleccionObjeto <= 3) {
      *nuevoObjeto = espadas[seleccionObjeto - 1];
      queue_insert(jugador->inventario, nuevoObjeto);
      aplicarEfectoObjeto(jugador, 1, espadas[seleccionObjeto - 1].efecto);
    } else {
      printf("Selección inválida. No se aplicó ningún objeto.\n");
      free(nuevoObjeto);
    }
    break;

  case 2:
    printf("Elige una armadura:\n");
    actualizarMenuActualCSV(5);
    for (int i = 0; i < 3; i++) {
      printf("%d. %s\n", i + 1, armaduras[i].nombre);
    }
    int seleccionObjeto2 = elegirOpcion(3, 5); // Menu de los objetos específicos
    if (seleccionObjeto2 >= 1 && seleccionObjeto2 <= 3) {
      *nuevoObjeto = armaduras[seleccionObjeto2 - 1];
      queue_insert(jugador->inventario, nuevoObjeto);
      aplicarEfectoObjeto(jugador, 2, armaduras[seleccionObjeto2 - 1].efecto);
    } else {
      printf("Selección inválida. No se aplicó ningún objeto.\n");
      free(nuevoObjeto);
    }
    break;

  case 3:
    printf("Elige un escudo:\n");
    actualizarMenuActualCSV(6);
    for (int i = 0; i < 3; i++) {
      printf("%d. %s\n", i + 1, escudos[i].nombre);
    }
    int seleccionObjeto3 = elegirOpcion(3, 6); // Menu de los objetos específicos
    if (seleccionObjeto3 >= 1 && seleccionObjeto3 <= 3) {
      *nuevoObjeto = escudos[seleccionObjeto3 - 1];
      queue_insert(jugador->inventario, nuevoObjeto);
      aplicarEfectoObjeto(jugador, 3, escudos[seleccionObjeto3 - 1].efecto);
    } else {
      printf("Selección inválida. No se aplicó ningún objeto.\n");
      free(nuevoObjeto);
    }
    break;

  default:
    printf("Selección inválida. No se aplicó ningún objeto.\n");
    free(nuevoObjeto);
  }
}

void menuPrincipal(int mapa[MAX][MAX], Personaje *jugador) {

  do {
    mostrarMenu();
    int opcion = elegirOpcion(6, 1); // Menu Principal
    switch (opcion) {
    case 1:
      inicializarMapa(mapa);
      *jugador = elegirPersonaje();
      elegirObjeto(jugador);
      actualizarMenuActualCSV(90);
      return;
    case 2://objetos
      actualizarMenuActualCSV(10);
      sleep(5);
      break;
    case 3://habilidades
      actualizarMenuActualCSV(11);
      sleep(5);
      break;
    case 4://creditos
      actualizarMenuActualCSV(12);
      sleep(5);
      break;
    case 5://ajustes
      actualizarMenuActualCSV(13);
      sleep(5);
      break;
    case 6:
      actualizarMenuActualCSV(99);
      printf("Saliendo...\n");
      return;
    default:
      printf("Opción no válida. Inténtalo de nuevo.\n");
    }
  } while (1);
}

// Habilidades predefinidas

// Función para elegir una habilidad
void elegirHabilidad(Personaje *jugador) {
  Habilidad habilidades[] = {
      {1, "Defensa sólida", "Aumenta la vida maxima", 20},
      {2, "Regeneración", "Regenera vida lentamente", 3},
      {3, "Fuerza bruta", "Aumenta el daño de ataque", 10},
  };

  int numHabilidades = 3;
  printf("¡Subiste de nivel! Elige una habilidad:\n\n");
  for (int i = 0; i < numHabilidades; i++) {
    printf("%d. %s - %s\n", i + 1, habilidades[i].nombre,
           habilidades[i].efecto);
  }

  int seleccion = elegirOpcion(3, 9); // menu de elegir habilidad

  if (seleccion >= 1 && seleccion <= numHabilidades) {
    Habilidad *nuevaHabilidad = (Habilidad *)malloc(sizeof(Habilidad));
    if (!nuevaHabilidad) {
      printf("Error al asignar memoria para la nueva habilidad.\n");
      return;
    }
    *nuevaHabilidad = habilidades[seleccion - 1];
    list_pushFront(jugador->habilidades, nuevaHabilidad);
    printf("Has aprendido la habilidad: %s\n\n", nuevaHabilidad->nombre);
    if (seleccion - 1 == 0)
    {
        aplicarDefensaSolida(jugador,nuevaHabilidad->efectoValor); 
    }
    if (seleccion - 1 == 0)
    {
        aplicarRegeneracion(jugador,nuevaHabilidad->efectoValor); 
    }
    if (seleccion - 1 == 0)
    {
        aplicarFuerzaBruta(jugador,nuevaHabilidad->efectoValor); 
    }
  } else {
    printf("Selección inválida. No se ha aprendido ninguna habilidad.\n");
  }
}

// Función para manejar la experiencia y subida de nivel
void ganarExperiencia(Personaje *jugador, int exp) 
{
  jugador->experiencia += exp;
  printf("\nHas ganado %d puntos de experiencia. Experiencia total: %d", exp,
         jugador->experiencia);

  // Verificar si sube de nivel
  int nivelActual = jugador->nivel;
  int expParaSubir =
      nivelActual * 100; // Definir la experiencia necesaria para subir de nivel
  if (jugador->experiencia >= expParaSubir) 
  {
    jugador->nivel++;
    jugador->experiencia -= expParaSubir; // Restar la experiencia utilizada para subir de nivel
    printf("\n¡Felicidades! Has subido al nivel %d\n", jugador->nivel);
    elegirHabilidad(jugador); // Pausar el juego y permitir que el jugador elija
                              // una habilidad

  }
}

void usarHabilidad(int mapa[MAX][MAX], Personaje *jugador, Enemigo *enemigos,
                 int *numEnemigos) 
{
int enemigosAfectados = 0;
for (int i = 0; i < *numEnemigos; i++) 
  {
  // Asegurarse de que el enemigo está en el mapa y no es el jugador mismo
  if (mapa[enemigos[i].x][enemigos[i].y] != 0 &&
      mapa[enemigos[i].x][enemigos[i].y] != jugador->id) 
    {
    enemigos[i].vida -= jugador->DanoBase;

    if (enemigos[i].vida <= 0) 
      {
      mapa[enemigos[i].x][enemigos[i].y] = 0;

      // Eliminar enemigo del array
      for (int j = i; j < *numEnemigos - 1; j++) {
        enemigos[j] = enemigos[j + 1];
      }
      (*numEnemigos)--;
      ganarExperiencia(jugador, (enemigosAfectados * 2));
      i--; // Ajustar el índice después de eliminar
      }

    enemigosAfectados++;

    }
  }  
}