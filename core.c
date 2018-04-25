#include "core.h"
#include "matrix_constants.h"

static int surroundings_chk(int matriz[P][N][M], int fila, int columna);
/***************************************************************************************************
FUNCION nextgen()

Para cada posición (células) de la matriz "main" (0), calcula su estado en la siguiente generación,
y lo copia en la matriz "buffer" (1)

Recibe: - Dirección array de 3 Dimensiones (2 x N x M) (mat 0 = main y mat 1 = buffer)

Devuelve: ---------

Requiere: Definición de constantes N (filas matriz) y M (columnas matriz)

**************************************************************************************************/
void nextgen(int world [P][N][M])
{
  int fila,columna;
  for(fila = 0; fila <= (N-1);fila++)
  {
    for(columna = 0; columna <= (M-1);columna++)
    {
      int cell,neighbours;                                                       // creo variable que indica el contenido de una célula y variable que cuenta la cantidad de "vecinos"
      cell = world [0][fila][columna];                                            // asigno a dicha variable el contenido de la célula
      neighbours = surroundings_chk(world,fila,columna);                // llamo a función que informa la cantidad de vecinos de la célula

      if((cell==ALIVE && (neighbours==2 || neighbours==3)) || (cell==DEAD && neighbours==3))
      {
        world[1][fila][columna] = ALIVE;                                         // si la célula está viva y tiene exactamente 2 o 3 vecinos ,o si está muerta y tiene exactamente 3 vecinos, estará viva
      }

      else
      {
        world[1][fila][columna] = DEAD;                                          // si la célula está viva y no tiene exactamente 2 o 3 vecinos, o está muerta y no tiene exactamente 3 vecinos, entonces muere
      }
      }

    }
  }

  /***************************************************************************************************
  FUNCION surroundings_chk()

  Determina, para una posición dada de un arreglo en 2 dimensiones, cuantas posiciones adyacentes contienen el caracter
  1, tomando en cuenta las diagonales. La adyacencia en los bordes de la matriz no comprende un salto de fila/columna

  Recibe: - Dirección array de 3 Dimensiones (2 x N x M) (mat 0 = main y mat 1 = buffer)

  Devuelve: Variable char con el número de celdas adyacentes que contienen un 1 (máximo 8)

  Requiere: Definición de constantes N (filas matriz) y M (columnas matriz)

  **************************************************************************************************/

  static int surroundings_chk(int matriz[P][N][M], int fila, int columna)
  {
    int  neighbours = 0;

    if((fila-1)>=0 && (columna-1)>=0 && matriz[0][fila-1][columna-1] == 1)  // chequeo posición arriba izquierda
    {
      neighbours++;
    }

    if((fila-1)>=0 && (columna+1)<M && matriz[0][fila-1][columna+1] == 1)  // chequeo posición arriba derecha
    {
      neighbours++;
    }

    if((fila+1)<N && (columna-1)>=0 && matriz[0][fila+1][columna-1] == 1)  // chequeo posición abajo izquierda
    {
      neighbours++;
    }

    if((fila+1)<N && (columna+1)<M && matriz[0][fila+1][columna+1] == 1)  // chequeo posición abajo derecha
    {
      neighbours++;
    }

    if(fila>=0 && (columna-1)>=0 && matriz[0][fila][columna-1] == 1)  // chequeo posición aizquierda
    {
      neighbours++;
    }

    if((fila-1)>=0 && columna>=0 && matriz[0][fila-1][columna] == 1)  // chequeo posición arriba
    {
      neighbours++;
    }

    if(fila>=0 && (columna+1)<M && matriz[0][fila][columna+1] == 1)  // chequeo posición derecha
    {
      neighbours++;
    }

    if((fila+1)<N && columna>=0 && matriz[0][fila+1][columna] == 1)  // chequeo posición abajo
    {
      neighbours++;
    }

    return neighbours;
  }

  /***************************************************************************************************
  FUNCION ini_world()

  inicializa aleatoreamente las celulas en world
  **************************************************************************************************/
void ini_world(int matrix[P][N][M])
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

/*SWAP_MATRIX permite copiar, en una matriz de 3 dimensiones, el contenido de
una dimensión siguiente, a la actual (de 1 a 0, de 2 a 1 y asi).  EL CONTENIDO
DE LA MATRIZ "0" SE PIERDE!!! ADEMÁS EL CONTENIDO DE LA MATRIZ N Y LA (N-1)
SERÁ EL MISMO*/
void swap_matrix (int matrix [P][N][M])
{
  int i,j,k;/*indices para moverme en la matriz*/
  for(i=0;i<N;i++)/*me muevo por la matriz con estos for*/
  {
    for(j=0;j<M;j++)
    {
      for(k=0;k<P-1;k++)
      {
        matrix[k][i][j]=matrix[k+1][i][j];/*copia de contenido*/
      }
    }
  }
}
