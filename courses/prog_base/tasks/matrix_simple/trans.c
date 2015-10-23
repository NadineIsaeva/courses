/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillRand(int mat[4][4]);
void rotateCCW180(int mat[4][4]);
void flipH(int mat[4][4]);
void transposMain(int mat[4][4]);
void printMatrix(int mat[4][4]);

int main () {
    int mat[4][4];
    srand(time(NULL));
    fillRand(mat);
    printMatrix(mat);


    rotateCCW180(mat);
     printMatrix(mat);

   flipH(mat);
    printMatrix(mat);

   transposMain(mat);
   printMatrix(mat);




}
void printMatrix(int mat[4][4]){
    int n,m;
    for (n=0; n<4; n++) {
    for (m=0; m<4; m++) {
       printf("%i\t",mat[n][m]);
    }
    printf("\n");
   }
   printf("\n");

}*/
void fillRand (int mat[4][4]) {
   int i,j;
   for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
        mat [i][j]= rand()%1999 - 999;
    }
   }
}

void rotateCCW180(int mat[4][4]){
int a,b,c,d,i,j;
int matrix[4][4];
for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
        matrix[i][j]=mat[i][j];
        }
}
for (a=0; a<4; a++) {
    for (b=0; b<4; b++) {
            c=3-a;
            d=3-b;
      mat[a][b]=matrix[c][d];
        }
}
}

void flipH(int mat[4][4]){
    int a,b,c,d,i,j;
    int matrix[4][4];
for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
        matrix[i][j]=mat[i][j];
        }
}
for (a=0; a<4; a++) {
    for (b=0; b<4; b++) {
         d=3-b;
      mat[a][b]=matrix[a][d];
        }
}
}

void transposMain(int mat[4][4]) {
    int a,b,i,j;
    int matrix[4][4];
    for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
        matrix[i][j]=mat[i][j];
        }
    }
    for (a=0; a<4; a++) {
    for (b=0; b<4; b++) {
      mat[a][b]=matrix[b][a];
        }
    }
}


