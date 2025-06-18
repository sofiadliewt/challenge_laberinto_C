# challenge_laberinto_C
# 🧩 Generador y Solucionador de Laberintos en C

Este programa genera laberintos aleatorios utilizando el algoritmo **Recursive Backtracker**, los muestra en consola y luego intenta resolverlos mediante **backtracking**. Está desarrollado en lenguaje **C** y permite personalizar el tamaño del laberinto dentro de ciertos límites.

## Características

- Generación de laberintos aleatorios.
- Solución del laberinto desde la entrada hasta la salida.
- Visualización en consola del laberinto generado y su solución.
- Caminos correctos marcados con `*`.
- Caminos fallidos marcados con `x`.

## Algoritmos usados

- **Recursive Backtracker** para crear los pasillos.
- **Backtracking (DFS)** para encontrar un camino válido desde la entrada (`E`) a la salida (`S`).

## Uso

1. Compilar el código:
   ```bash
   gcc -o laberinto laberinto.c
