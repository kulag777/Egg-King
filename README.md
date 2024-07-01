# PROYECTO "EGG OF KING"

Para ejecutar el juego hay que usar estos comandos en la shell:
````console
cd Python
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

### Segun la opcion que se seleccione, se abrira submenus:
### 1) Nueva partida
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
### Segun el objeto que se seleccione, se pueden elegir las siguientes opciones:

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

`void aplicarDefensaSolida(Personaje *jugador, int aumentoVidaMax);`

`void aplicarRegeneracion(Personaje *jugador, int regeneracion);`

`void aplicarFuerzaBruta(Personaje *jugador, int aumentoDanio);`

`void exportarHabilidades(Personaje *jugador);`

`void exportarVida(int vida);`

`void menuMuerte(Personaje *jugador);`

`void setNonBlockingMode(int enable);`

`void limpiarBufferEntrada();`

`void actualizarCSV(int seleccionada);`

`void actualizarMenuActualCSV(int menuID);`

`int elegirOpcion(int opciones, int menuID);`

`void mostrarHabilidades(Personaje *jugador);`

`void mostrarMenu();`

`Personaje elegirPersonaje();`

`void inicializarMapa(int mapa[MAX][MAX]);`

`void moverPersonaje(Personaje *jugador, int mapa[MAX][MAX], char direccion);`

`int randRange(int min, int max);`

`void generarEnemigos(Enemigo *enemigos, int numEnemigos, Personaje *jugador, int mapa[MAX][MAX]);`

`void moverEnemigos(Enemigo *enemigos, int numEnemigos, Personaje *jugador, int mapa[MAX][MAX]);`

`void exportarDatos(int mapa[MAX][MAX], Personaje *jugador);`

`void aplicarEfectoObjeto(Personaje *jugador, int tipoObjeto, int efecto);`

`void elegirObjeto(Personaje *jugador);`

<br>

## --> PROTOTIPOS DE FUNCIONES EN PYTHON

`def read_actual_menu_from_csv(filename):`

`def read_menu_from_csv(filename):`

`def read_map_from_csv(filename):`

`def draw_menu_principal(screen):`

`def draw_players(screen):`

`def draw_choose_weapon(screen):`

`def draw_death_menu(screen):`

`def creditos(screen):`

`def draw_Habilidades(screen):`

`def exitGame(screen):`

`def draw_objects(screen):`

`def get_player_image(character, object_choice, tipo_choice):`

`def read_character_choice_from_csv(filename):`

`def draw_map(screen, map, character, object_choice, tipo_choice, vidaActual):`

`def draw_object_menu(screen):`

`def draw_config(screen):`

<hr>

<br>

## --> TDA´S
En la carpeta `tdas` se encuentran implementados los TDAs que fueron usado para programar el juego 

## --> CONTRIBUCIONES HECHAS POR CADA UNO

## --> CREDITOS  
<hr>
<br>
