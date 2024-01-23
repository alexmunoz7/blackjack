#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARTAS 52
#define VALORES_CARTA 13
#define MAXIMA_MANO 10

// Representación de las cartas
char *valores[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *palos[] = {"Corazones", "Diamantes", "Picas", "Treboles"};

// Estructura para una carta
struct carta {
    char *valor;
    char *palo;
    int valorNumerico;
};

struct carta mazo[TOTAL_CARTAS];
struct carta manoJugador[MAXIMA_MANO];
int numCartasJugador = 0;
int sumaJugador = 0;
char eleccion;


void mostrarCarta(struct carta c) {
    printf("  %s de %s\n", c.valor, c.palo);
}

int sumarMano(struct carta mano[], int numCartas) {
    int suma = 0;
    for (int i = 0; i < numCartas; i++) {
        suma += mano[i].valorNumerico;
    }
    return suma;
}


int main()
{

    for (int i = 0; i < TOTAL_CARTAS; i++) {
        mazo[i].valor = valores[i % VALORES_CARTA];
        mazo[i].palo = palos[i / VALORES_CARTA];
        mazo[i].valorNumerico = (i % VALORES_CARTA) + 2;
        if (mazo[i].valorNumerico > 10) mazo[i].valorNumerico = 10;
        if (i % VALORES_CARTA == VALORES_CARTA - 1) mazo[i].valorNumerico = 11;
    }

    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        int j = rand() % TOTAL_CARTAS;
        struct carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }


    printf("Bienvenido al Blackjack!\n");

    manoJugador[numCartasJugador++] = mazo[0];
    manoJugador[numCartasJugador++] = mazo[1];
    sumaJugador = sumarMano(manoJugador, numCartasJugador);

    printf("Tus cartas:\n");
    mostrarCarta(manoJugador[0]);
    mostrarCarta(manoJugador[1]);
    printf("suma total: %d\n", sumaJugador);

    while (sumaJugador < 21) {
        printf("¿Quieres otra carta? (s/n): ");
        scanf(" %c", &eleccion);

        if (eleccion == 's' || eleccion == 'S') {
            manoJugador[numCartasJugador] = mazo[numCartasJugador];
            sumaJugador = sumarMano(manoJugador, ++numCartasJugador);

            printf("Nueva carta:\n");
            mostrarCarta(manoJugador[numCartasJugador - 1]);
            printf("suma total: %d\n", sumaJugador);
        } else {
            break;
        }
    }

    if (sumaJugador == 21) {
        printf("¡Blackjack! Has ganado.\n");
    } else if (sumaJugador > 21) {
        printf("Te has pasado. Fin del juego.\n");
    } else {
        printf("Te has plantado con %d. Fin del juego.\n", sumaJugador);
    }

    return 0;
}
