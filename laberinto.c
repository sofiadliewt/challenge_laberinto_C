
#include <stdio.h>   // para printf / scanf
#include <stdlib.h>  // para rand, srand
#include <time.h>    // para time (semilla aleatoria)

//VARIABLES GLOBALES

char lab[100][100];    // matriz del laberinto (hasta 99×99)
int filas, columnas;   // dimensiones reales elegidas por el usuario

//FUNCION: mostrar Imprime el laberinto en pantalla.

void mostrar() {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++)
            printf("%c ", lab[i][j]);
        printf("\n");
    }
}
// FUNCION: llenar_con_muros Rellena toda la matriz con paredes ('#')
void llenar_con_muros() {
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            lab[i][j] = '#';
}

//FUNCION: mezclar Baraja aleatoriamente un arreglo de 4 direcciones. (Algoritmo Fisher‑Yates simplificado para 4 elementos).
void mezclar(int d[4][2]) {
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;                 // índice aleatorio 0‑3
        //intercambio de pares (x,y)
        int temp0 = d[i][0], temp1 = d[i][1];
        d[i][0] = d[r][0]; d[i][1] = d[r][1];
        d[r][0] = temp0;  d[r][1] = temp1;
    }
}

//FUNCION: generar Algoritmo “recursive backtracker” para tallar pasillos. Parte de (x,y), abre esa celda y se expande en saltos de 2.

void generar(int x, int y) {
    lab[x][y] = ' ';                        // abre la celda actual
    int dir[4][2] = { {-2,0},{0,2},{2,0},{0,-2} }; // saltos N,E,S,O
    mezclar(dir);                           // barajar orden aleatorio

    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];             // nueva celda 2 pasos
        int ny = y + dir[i][1];
        //solo abrir si está dentro del borde y es pared
        if (nx > 0 && ny > 0 &&
            nx < filas - 1 && ny < columnas - 1 &&
            lab[nx][ny] == '#') {

            //romper la pared intermedia (paso de 1)
            lab[x + dir[i][0]/2][y + dir[i][1]/2] = ' ';
            //recursión: continuar desde la nueva celda
            generar(nx, ny);
        }
    }
}

//FUNCION: resolver Backtracking para encontrar el camino E  S. Devuelve 1 si encontró salida; 0 si no.

int resolver(int x, int y) {
    //Caso base: llegó a la salida
    if (lab[x][y] == 'S') return 1;

    /* Si es pared o ya visitado, descartar ruta */
    if (lab[x][y] != ' ' && lab[x][y] != 'E') return 0;

    // Marcar la celda como parte del camino tentativo
    if (lab[x][y] != 'E') lab[x][y] = '*';

    //Explorar en las 4 direcciones (DFS)
    if (resolver(x+1, y) || resolver(x-1, y) ||
        resolver(x, y+1) || resolver(x, y-1))
        return 1;                           // alguna funcionó

    //Ninguna dirección funcionó  marca de camino muerto 
    if (lab[x][y] != 'E') lab[x][y] = 'x';
    return 0;
}

//FUNCION PRINCIPAL

int main() {
    int temp_filas, temp_columnas;

    srand(time(NULL));                      // semilla aleatoria

    //Leer dimensiones
    printf("Ingrese el número de filas del laberinto (5‑99): ");
    scanf("%d", &temp_filas);
    printf("Ingrese el número de columnas del laberinto (5‑99): ");
    scanf("%d", &temp_columnas);

    //Limitar rango y forzar números impares
    if (temp_filas    < 5)  temp_filas    = 5;
    if (temp_filas    > 99) temp_filas    = 99;
    if (temp_columnas < 5)  temp_columnas = 5;
    if (temp_columnas > 99) temp_columnas = 99;

    if (temp_filas    % 2 == 0) temp_filas++;
    if (temp_columnas % 2 == 0) temp_columnas++;

    filas    = temp_filas;
    columnas = temp_columnas;

    printf("\nTamaño final: %d × %d\n\n", filas, columnas);

    //Generar laberinto
    llenar_con_muros();     // todo paredes
    generar(1, 1);          // carve desde (1,1)

    // Posiciones de entrada y salida 
    lab[0][1]                     = 'E';           // Entrada (fila 0)
    lab[filas-1][columnas-2]      = 'S';           // Salida (última fila)

    printf("Laberinto generado:\n\n");
    mostrar();

    // Resolver laberinto
    if (resolver(0, 1)) {
        printf("\nLaberinto resuelto:\n");
        printf("   '*'  -> camino correcto\n");
        printf("   'x'  -> caminos fallidos\n\n");
        mostrar();
    } else {
        printf("\nNo se encontró solución.\n");
    }

    return 0;
}
