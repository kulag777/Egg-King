# PROYECTO "EGG OF KING"

Para ejecutar el juego hay que usar estos comandos en la shell:
````console
cd Python
````

Escribir:
````console
pip install pygame
````

luego escribir:
````console
python game.py
````

Y luego darle al boton:
````console
"Run"
````
<br>

## --> MENU PRINCIPAL

El codigo te abre un menu donde tu eliges que opcion te interesa.
````bash
Menu principal:
1) Nueva partida
2) Ver objetos
3) Ver habilidades
4) Créditos
5) Ajustes
6) Salir
````

### Segun la opcion que se seleccione, se abriran distintos submenus:
`1) Nueva partida` Iniciar una nueva partida
````bash
Elige un personaje:
1) Kulag
2) Cris
3) Gogo
4) Javi
````
🡫🡫🡫🡫🡫🡫🡫 
````bash
Elige un tipo de objeto:
1) Espada
2) Armadura
3) Escudo
````
🡫🡫🡫🡫🡫🡫🡫
#### 1) Espada
````bash
Elige un tipo de espada:
1) Espada de Fuego
2) Espada de Hielo
3) Espada de Trueno
````
#### 2) Armadura
````bash
Elige un tipo de Armadura:
1) Armadura de Dragón
2) Armadura de Acero
3) Armadura de Diamante
````
#### 3) Escudo
````bash
Elige un tipo de Armadura:
1) Armadura de Plata
2) Armadura de Oro 
3) Armadura de Diamante
````
### --> Despues de seleccionar el objeto preferido, se inicia el juego automaticamente. <---
<br>

`2) Ver objetos` Se mostrara los objetos disponibles para seleciconar antes de que se inicie la partida.

`3) Ver Habilidades` Se mostrara las habilidades disponibles para cuando se sube de nivel mientras se juega.

`4) Créditos` Se mostraran los creditos.

`5) Ajustes ` Se mostraran los ajustes disponibles.

`6) Salir` Salir del juego.

## --> Structs

Estructura que guarda la informacion del personaje.
````c
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
````

Estructura que guarda la informacion del enemigo.
````c
typedef struct {
    int id;
    int vida;
    int x, y;
} Enemigo;
````

Estructura para almacenar los tipos de habilidades y especificaciones.
````c
typedef struct {
    int id;
    char nombre[50];
    char efecto[50];
    int efectoValor;
} Habilidad;
````

Estructura para almacenar los tipos de objetos y especificaciones.
````c
typedef struct {
    int id;
    char nombre[50];
    int efecto;
} Objeto;

````
<br>

## --> PROTOTIPOS DE FUNCIONES EN C

### Aplicar y exportar habilidades
````c
void aplicarDefensaSolida(Personaje *jugador, int aumentoVidaMax); 

void aplicarRegeneracion(Personaje *jugador, int regeneracion);

void aplicarFuerzaBruta(Personaje *jugador, int aumentoDanio);

void exportarHabilidades(Personaje *jugador);
````
### Funciones que sirven para mostrar en el Python
##### Actualiza los CSV
````c
void actualizarCSV(int seleccionada);

void actualizarMenuActualCSV(int menuID); 

void exportarVida(int vida);

void menuMuerte(Personaje *jugador); 

void exportarDatos(int mapa[MAX][MAX], Personaje *jugador);
````
##### Acciones del jugador
````c
Personaje elegirPersonaje();

int elegirOpcion(int opciones, int menuID);

void moverPersonaje(Personaje *jugador, int mapa[MAX][MAX], char direccion);

void elegirObjeto(Personaje *jugador);

void aplicarEfectoObjeto(Personaje *jugador, int tipoObjeto, int efecto);

````
##### Acciones del juego
````c
void mostrarMenu();

void inicializarMapa(int mapa[MAX][MAX]);

void generarEnemigos(Enemigo *enemigos, int numEnemigos, Personaje *jugador, int mapa[MAX][MAX]);

int randRange(int min, int max);

void moverEnemigos(Enemigo *enemigos, int numEnemigos, Personaje *jugador, int mapa[MAX][MAX]);

````
##### Extras
````c
void limpiarBufferEntrada();

void setNonBlockingMode(int enable);
````
## --> PROTOTIPOS DE FUNCIONES EN PYTHON

### Leer archivos CSV 
````python
def read_actual_menu_from_csv(filename):

def read_menu_from_csv(filename):

def read_map_from_csv(filename):
  
def read_character_choice_from_csv(filename):
````
### Mostrar texturas en Output
````python
def draw_menu_principal(screen):
  
def draw_players(screen):
  
def draw_choose_weapon(screen):

def draw_death_menu(screen):

def draw_creditos(screen):

def draw_Habilidades(screen):

def draw_exitGame(screen):

def draw_objects(screen):
  
def draw_map(screen, map, character, object_choice, tipo_choice, vidaActual):

def draw_object_menu(screen):

def draw_config(screen):

def get_player_image(character, object_choice, tipo_choice):
````
## --> TDA´S
Los TDAs cola y list en este código ayudan a gestionar de manera eficiente el inventario y las habilidades del jugador. La cola asegura que los objetos se procesen en el orden en que se obtienen, mientras que la lista permite una gestión flexible de las habilidades, permitiendo al jugador adquirir y utilizar nuevas habilidades a medida que avanza en el juego. Estos TDAs son esenciales para la organización y manipulación de datos en este juego estilo roguelike, proporcionando estructuras robustas y eficientes para las operaciones necesarias.

## --> Posibles errores en la aplicación (Bugs)

* Si llegas a reiniciar el programa en C y el programa en python no, ocurrira un error en la pantalla que se vera mal, esto se puede solucionar terminando el programa en python desde la shell apretando `ctrl + z` y ejecutando `python game.py` desde la Shell.
* Si despues de jugar una partida intentas salir apretando la opcion 6 en el menu principal, el programa de PYTHON si finaliza mientras que el de C no. 



## --> CONTRIBUCIONES HECHAS POR CADA UNO

<br>

* Benjamin Espinoza : Yo personalmente me encarge de que el codigo de Python funcionara correctamente, y la logica del mismo la idee yo, que con la ayuda de los demas, el codigo funciona idealmente. Junto con esto las exportaciones que hay en C algunos los hice yo y otros los hizo cristobal. Tambien ayude en hacer el codigo de C, ayudando en errores y logica mal implementada.

<br>

* Cristobal Martinez: Yo me encarge de hacer el codigo de C, pense el como usar los distintos TDA's y como implementarlos para poder incluirlos y que funcionen. Tambien ayude en el codigo de Python, al tener que exportar informacion para que este lo lea de manera adecuada y que no muestre otra pantalla u otro menu.

<br>

* Javiera Muñoz : Yo me encargue de crear casi todos los sprites e implementarlos en el codigo de python junto a la ayuda de Cristobal que me ayudaba exportando la informacio de C a Python, implemente la funcion de la barra de vida, configure en C y Python la funcion para que al seleccionar personaje y objeto se muestre correctamente la combinacion que se eligio, tambien ayude con la logica del juego en C y solucione bugs que transcurrian durante la programacion del juego.

<br>

* Diego Rivera : Yo tambien fui el encargado de hacer sprites e implementarlos en el codigo de Python, ayude a organizar los nombres de los mismos para que se ejecute en el codigo de python, tambien ayude en la logica del juego en C, ayudando en la idea de los structs y solucionando bugs de la visualizacion del menu en el codigo.
  