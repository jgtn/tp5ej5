#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "i_o.h"
#include "core.h"

/*CONSTANTES DE MAIN*/
#include "matrix_constants.h"

/*PROTOTIPOS*/
static void ini_world(int matrix[P][N][M]);

/*MAIN*/
int main(void)
{
  int gen = 0; /*La primer generación (hardcodeada) es la 0*/
  int world[P][N][M]; /*Matriz de 3 dimensiones que contiene P (2) matrices (una "actual" y una "buffer") que representan el mundo en 2 dimensiones*/

  ini_world(world); /*Se inicializa que células viven y qué celulas mueren en*/

  printf("Bienvenido al Juego de la Vida, para ver la generación sucesiva presione ENTER, para salir del juego presione 'q'\n");

  while (waitChar()) /*Si el usuario ingresa un ENTER, se recibe un 1 y se ejecuta la siguiente generación, si ingresa una 'q' se recibe un 0 y se termina el juego*/
  {
    print_matrix(world, gen); /*Se envía a pantalla la matriz world[0] "actual"*/
    nextgen(world); /*Se hace el cálculo de la nueva generación y se guarda en la matriz[1] "buffer"*/
    swap_matrix(world); /*Lo contenido en la matriz[1] "buffer" es copiado a la matriz[0] "actual"*/
    gen++;
  }

  printf("Juego finalizado en la %d° generación\n", gen);

  return 0;
}



/*FUNCION INI_WORLD*/
static void ini_world(int matrix[P][N][M])
{
  srand(time(NULL)); /*Para generar un valor aleatorio*/

  int i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < M; j++)
    {
      matrix[0][i][j] = (rand()%2); /*Cada célula se inicializa como viva (1) o muerta (0) de forma aleatoria*/
    }
  }
}
