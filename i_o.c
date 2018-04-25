/******************************************************************************
                                    I_O.c
  Este modulo contiene las funciones que manejan la interaccion con el usuario.
  GRUPO 4 PROGRAMCION I
 ******************************************************************************/

 #include <stdio.h>
 #include "I_O.h"

/*******************************************************************************
                        FUNCIONES GLOBALES
 ******************************************************************************/

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

 /*WAITCHAR: Espera a que se ingrese 'Q','q' o enter y sale.
 Devuelve un 0 si se ingreso una 'q' o 'Q' o 1 si se ingreso '\n'.*/

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
