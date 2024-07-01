import csv
from typing import Optional
import pygame
import time
import CONSTANTES_PYTHON as C
import sys

personajes = {7: 'Kulag', 8: 'Cris', 9: 'Gogo', 10: 'Javi'}


## LEER CSV DEL JUEGO
def read_actual_menu_from_csv(filename):
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            return int(row[0])
    return 0


def read_menu_from_csv(filename):
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            return int(row[0])
    return 0


def read_map_from_csv(filename):
    """Lee el mapa desde un archivo CSV y lo convierte en una matriz."""
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        map = []
        for row in reader:
            # Eliminar cualquier cadena vacía resultante de comas al final
            cleaned_row = [tile for tile in row if tile]
            map.append([int(tile) for tile in cleaned_row])
    return map


def read_character_choice_from_csv(filename):
    """Lee el archivo CSV que contiene la elección del personaje."""
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            return row[0].strip(
            )  # Retorna el contenido completo de la primera celda, sin espacios adicionales


# Función para obtener la imagen del jugador segun el objeto seleccionado
def get_player_image(character, object_choice, tipo_choice):
    base_path = 'imagenes/'
    return pygame.image.load(
        f'{base_path}{object_choice}{tipo_choice}{character}.png'
    ).convert_alpha()


## DIBUJAR LOS DISTINTOS MENUS
def draw_menu_principal(screen):
    """Dibuja el menú en la pantalla."""
    background = pygame.image.load('imagenes/menu/menu1.png').convert()
    screen.blit(background, (0, 0))


def draw_players(screen):
    """Dibuja los personajes en la pantalla según la opción seleccionada."""
    background = pygame.image.load(
        'imagenes/menu/eleccionPersonaje.png').convert()
    screen.blit(background, (0, 0))


def draw_choose_weapon(screen):
    """Dibuja la selección de armas en la pantalla."""
    background = pygame.image.load(
        'imagenes/menu/eleccionObjetos.png').convert()
    screen.blit(background, (0, 0))


def draw_death_menu(screen):
    """Dibuja el menú de muerte en la pantalla."""
    background = pygame.image.load('imagenes/menu/muerte.png').convert()
    screen.blit(background, (0, 0))


def draw_creditos(screen):
    """Dibuja los creditos."""
    background = pygame.image.load('imagenes/menu/creditos.png').convert()
    screen.blit(background, (0, 0))


def draw_Habilidades(screen):
    """Dibuja las habilidades."""
    background = pygame.image.load(
        'imagenes/menu/verHabilidades.png').convert()
    screen.blit(background, (0, 0))


def draw_exitGame(screen):
    """dibuja la despedida."""
    background = pygame.image.load('imagenes/menu/salida.png').convert()
    screen.blit(background, (0, 0))


def draw_objects(screen):
    """Dibuja el menú en la pantalla."""
    background = pygame.image.load('imagenes/menu/verObjetos.png').convert()
    screen.blit(background, (0, 0))


def draw_object_menu(screen):
    """Dibuja los objetos en la pantalla."""
    background = pygame.image.load('imagenes/menu/verObjetos.png').convert()
    screen.blit(background, (0, 0))


def draw_config(screen):
    """Dibuja los ajustes."""
    background = pygame.image.load('imagenes/menu/ajustes.png').convert()
    screen.blit(background, (0, 0))


def draw_map(screen, map, character, object_choice, tipo_choice, vidaActual):
    background = pygame.image.load('imagenes/mapa.png').convert()
    screen.blit(background, (0, 0))

    player_image = get_player_image(character, object_choice, tipo_choice)

    for y in range(min(C.HEIGHT, len(map))):
        for x in range(min(C.WIDTH, len(map[y]))):
            if map[y][x] == 0:
                continue
            elif map[y][x] in personajes.keys():  # Si es un personaje
                screen.blit(player_image, (x * C.TILE_SIZE, y * C.TILE_SIZE))

                vidaActual = read_actual_menu_from_csv('vida.csv')

                if vidaActual > 80:
                    vida_image = pygame.image.load(
                        'imagenes/barraDeVida/fullvida.png').convert_alpha()
                elif vidaActual > 60:
                    vida_image = pygame.image.load(
                        'imagenes/barraDeVida/80vida.png').convert_alpha()
                elif vidaActual > 40:
                    vida_image = pygame.image.load(
                        'imagenes/barraDeVida/60vida.png').convert_alpha()
                elif vidaActual > 20:
                    vida_image = pygame.image.load(
                        'imagenes/barraDeVida/40vida.png').convert_alpha()
                elif vidaActual > 0:
                    vida_image = pygame.image.load(
                        'imagenes/barraDeVida/20vida.png').convert_alpha()
                else:
                    vida_image = pygame.image.load(
                        'imagenes/barraDeVida/0vida.png').convert_alpha()

                screen.blit(vida_image, (440, -20))
            else:
                enemy_image = pygame.image.load(
                    'imagenes/enemigo1.png').convert_alpha()
                screen.blit(enemy_image, (x * C.TILE_SIZE, y * C.TILE_SIZE))


def main():
    """Función principal para inicializar pygame y correr el juego."""
    pygame.init()
    screen = pygame.display.set_mode(
        (C.WIDTH * C.TILE_SIZE, C.HEIGHT * C.TILE_SIZE))
    pygame.display.set_caption('Egg King')
    clock = pygame.time.Clock()

    pygame.mixer.init()
    pygame.mixer.music.load('eggKingMusic.mp3')
    pygame.mixer.music.play(-1)
    pygame.mixer.music.set_volume(0.5)

    running = True
    game_active = False
    death_menu = False

    character = None

    object_choice = 'Espada/'  # Valor predeterminado inicializado
    tipo_choice = 'EspadaFuego'  # Valor predeterminado inicializado

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        menuActual = read_actual_menu_from_csv('menuActual.csv')
        vidaActual = read_actual_menu_from_csv('vida.csv')

        if menuActual == 1:  # MENU PRINCIPAL
            screen.fill(C.BACKGROUND_COLOR)
            draw_menu_principal(screen)
            pygame.display.flip()

        elif menuActual == 2:  # ELECCION PERSONAJE
            screen.fill(C.BACKGROUND_COLOR)
            draw_players(screen)

            pygame.display.flip()

        elif menuActual == 3:  # ELECCION OBJETOS
            screen.fill(C.BACKGROUND_COLOR)
            draw_choose_weapon(screen)
            pygame.display.flip()

        if menuActual == 4:
            screen.fill(C.BACKGROUND_COLOR)
            background = pygame.image.load(
                'imagenes/menu/eleccionEspada.png').convert()
            screen.blit(background, (0, 0))
            pygame.display.flip()
            iniciar = False
            clase = -1  # Valor inicial indicando que no se ha leído correctamente
            while clase not in [1, 2, 3]:
                clase = read_menu_from_csv('registro_menu.csv')
            object_choice = 'Espada/'
            if clase == 1:
                tipo_choice = 'EspadaFuego'
                iniciar = True
            elif clase == 2:
                tipo_choice = 'EspadaHielo'
                iniciar = True
            elif clase == 3:
                tipo_choice = 'EspadaRayo'
                iniciar = True

            game_active = True  # opciones espadas

        elif menuActual == 5:
            screen.fill(C.BACKGROUND_COLOR)
            background = pygame.image.load(
                'imagenes/menu/eleccionArmadura.png').convert()
            screen.blit(background, (0, 0))
            pygame.display.flip()
            iniciar = False
            clase = -1  # Valor inicial indicando que no se ha leído correctamente

            while clase not in [1, 2, 3]:
                clase = read_menu_from_csv('registro_menu.csv')
            object_choice = 'Armadura/'
            if clase == 1:
                tipo_choice = 'ArmaduraDragon'
                iniciar = True
            elif clase == 2:
                tipo_choice = 'ArmaduraAcero'
                iniciar = True
            elif clase == 3:
                tipo_choice = 'ArmaduraDiamante'
                iniciar = True

            game_active = True  # opciones armaduras

        elif menuActual == 6:
            screen.fill(C.BACKGROUND_COLOR)
            background = pygame.image.load(
                'imagenes/menu/eleccionEscudo.png').convert()
            screen.blit(background, (0, 0))
            pygame.display.flip()
            iniciar = False
            clase = -1  # Valor inicial indicando que no se ha leído correctamente

            while clase not in [1, 2, 3]:
                clase = read_menu_from_csv('registro_menu.csv')
            object_choice = 'Escudo/'
            if clase == 1:
                tipo_choice = 'EscudoPlata'
                iniciar = True
            elif clase == 2:
                tipo_choice = 'EscudoOro'
                iniciar = True
            elif clase == 3:
                tipo_choice = 'EscudoDiamante'
                iniciar = True

            game_active = True  # opciones escudos

        if game_active:
            pygame.display.flip()
            map = read_map_from_csv('mapa.csv')
            screen.fill(C.BACKGROUND_COLOR)
            character = read_character_choice_from_csv('personajes.csv')
            draw_map(screen, map, character, object_choice, tipo_choice,
                     vidaActual)
            pygame.display.flip()

            if menuActual == 15:
                game_active = False
                death_menu = True

        elif death_menu:
            screen.fill(C.BACKGROUND_COLOR)
            draw_death_menu(screen)
            pygame.display.flip()
            if menuActual == 1:
                death_menu = False

        elif menuActual == 10:  # VER OBJETOS
            screen.fill(C.BACKGROUND_COLOR)
            draw_object_menu(screen)
            pygame.display.flip()
            pygame.time.wait(5000)

        elif menuActual == 11:  # VER HABILIDADES
            screen.fill(C.BACKGROUND_COLOR)
            draw_Habilidades(screen)
            pygame.display.flip()
            pygame.time.wait(5000)

        elif menuActual == 12:  # CREDITOS
            screen.fill(C.BACKGROUND_COLOR)
            draw_creditos(screen)
            pygame.display.flip()
            pygame.time.wait(5000)

        elif menuActual == 13:
            screen.fill(C.BACKGROUND_COLOR)
            draw_config(screen)
            pygame.display.flip()
            pygame.time.wait(5000)

        elif menuActual == 99:  # SALIR
            screen.fill(C.BACKGROUND_COLOR)
            draw_exitGame(screen)
            pygame.display.flip()
            pygame.time.wait(5000)
            pygame.quit()  #FINALIZA EL JUEGO Y EL PYTHON
            sys.exit()

        pygame.display.flip()
        clock.tick(30)  # Mantiene una velocidad de fotogramas constante


if __name__ == "__main__":
    main()
