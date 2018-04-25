#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*CONSTANTES DE MAIN*/
#define N 10 /*Filas para la matriz de world*/
#define M 10 /*Columnas para la matriz de world*/
#define P 2 /*Cantidad de matrices world, la 0 es la "actual" que se imprime*, la 1 es la "buffer"*/
/*CONSTANTES DE NEXTGEN*/
#define DEAD 0
#define ALIVE 1

/*PROTOTIPOS*/
void ini_world(int matrix[P][N][M]);
void nextgen(int world[P][N][M]);
void swap_matrix (int[P][N][M]);
void print_matrix(int[P][N][M],int);
int waitChar(void);
int surroundings_chk(int matriz[P][N][M], int fila, int columna);

/*MAIN*/
int main(void)
{
  int gen = 0; /*La primer generación (hardcodeada) es la 0*/
  int world[P][N][M]; /*Matriz de 3 dimensiones que contiene P (2) matrices (una "actual" y una "buffer") que representan el mundo en 2 dimensiones*/

  ini_world(world); /*Se inicializa que células viven y qué celulas mueren en*/

  printf("Bienvenido al Juego de la Vida, para ver la generación sucesiva presione ENTER, para salir del juego presiones 'q'\n");

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

  Devuelve: variable char con el número de celdas adyacentes que contienen un 1 (máximo 8)

  Requiere: Definición de constantes N (filas matriz) y M (columnas matriz)

  **************************************************************************************************/

  int surroundings_chk(int matriz[P][N][M], int fila, int columna)
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



/*PRINT_MATRIX imprime la matriz "0" de una matriz tridimensional,
los valores estarán separados por "|" y para que se muentre correctamente
en la consola los valores o caracteres deberán ocupar solo 1 espacio*/
void print_matrix(int matrix [P][N][M],int gen)
{
  printf("Generación número:%d\n\n",gen );
  int i,j;/*indices para moverme en la matriz*/
  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      if (matrix[0][i][j] == ALIVE)
      {
        printf("|%c", '*');/*Se imprime un '*' si está vivo*/
      }
      else
      {
        printf("|%c", ' ');/*Se imprime un ' ' si está vivo*/
      }
    }
    printf("|\n");
  }

}



/*FUNCIÓN WAITCHAR*/
int waitChar(void)
{
  int caracter;
  while( ( (caracter=getchar()) !='\n') && (caracter!='q') && (caracter!='Q') ); //solo sale cuando ingresan enter, 'q' o 'Q'
  if( (caracter=='q') || (caracter=='Q') )
  {
    return 0;     //devuelve 0 si hubo alguna q o Q entre los caracteres ingresados
  }
  else
  {
    return 1;   //devuelve 1 si apretaron enter
  }
}
