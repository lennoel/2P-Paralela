#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de la matriz dispersa
typedef struct {
    int filas;
    int columnas;
    int noCeros;         // Número de elementos no cero
    int *valores;        // Valores de los elementos no cero
    int *indicesCol;     // Índices de las columnas de los elementos no cero
    int *punterosFilas;  // Punteros de filas (almacenan el inicio de cada fila en indicesCol y valores)
} MatrizDispersa;

// Función para crear una matriz dispersa
MatrizDispersa* crearMatrizDispersa(int filas, int columnas, int noCeros) {
    MatrizDispersa *matriz = (MatrizDispersa *)malloc(sizeof(MatrizDispersa));
    matriz->filas = filas;
    matriz->columnas = columnas;
    matriz->noCeros = noCeros;
    matriz->valores = (int *)malloc(noCeros * sizeof(int));
    matriz->indicesCol = (int *)malloc(noCeros * sizeof(int));
    matriz->punterosFilas = (int *)malloc((filas + 1) * sizeof(int));
    return matriz;
}

// Función para liberar la memoria de una matriz dispersa
void liberarMatrizDispersa(MatrizDispersa *matriz) {
    free(matriz->valores);
    free(matriz->indicesCol);
    free(matriz->punterosFilas);
    free(matriz);
}

// Función para multiplicar dos matrices dispersas
MatrizDispersa* multiplicarMatricesDispersas(MatrizDispersa *A, MatrizDispersa *B) {
    if (A->columnas != B->filas) {
        fprintf(stderr, "Error: Las matrices no se pueden multiplicar debido a dimensiones incompatibles.\n");
        exit(EXIT_FAILURE);
    }

    // Estimación inicial del tamaño de la matriz resultado
    int noCeros = 0;
    int *filaNoCeros = (int *)calloc(A->filas * B->columnas, sizeof(int));

    for (int i = 0; i < A->filas; i++) {
        for (int j = A->punterosFilas[i]; j < A->punterosFilas[i + 1]; j++) {
            int col = A->indicesCol[j];
            for (int k = B->punterosFilas[col]; k < B->punterosFilas[col + 1]; k++) {
                int colB = B->indicesCol[k];
                if (filaNoCeros[i * B->columnas + colB] == 0) {
                    noCeros++;
                    filaNoCeros[i * B->columnas + colB] = 1;
                }
            }
        }
    }

    MatrizDispersa *C = crearMatrizDispersa(A->filas, B->columnas, noCeros);

    noCeros = 0;
    for (int i = 0; i < A->filas; i++) {
        C->punterosFilas[i] = noCeros;
        for (int j = A->punterosFilas[i]; j < A->punterosFilas[i + 1]; j++) {
            int col = A->indicesCol[j];
            for (int k = B->punterosFilas[col]; k < B->punterosFilas[col + 1]; k++) {
                int colB = B->indicesCol[k];
                int val = A->valores[j] * B->valores[k];

                int encontrado = 0;
                for (int l = C->punterosFilas[i]; l < noCeros; l++) {
                    if (C->indicesCol[l] == colB) {
                        C->valores[l] += val;
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    C->valores[noCeros] = val;
                    C->indicesCol[noCeros] = colB;
                    noCeros++;
                }
            }
        }
    }
    C->punterosFilas[A->filas] = noCeros;

    free(filaNoCeros);
    return C;
}

// Función para imprimir una matriz dispersa
void imprimirMatrizDispersa(MatrizDispersa* matriz) {
    printf("Valores: ");
    for (int i = 0; i < matriz->noCeros; i++) {
        printf("%d ", matriz->valores[i]);
    }
    printf("\nÍndices de Columnas: ");
    for (int i = 0; i < matriz->noCeros; i++) {
        printf("%d ", matriz->indicesCol[i]);
    }
    printf("\nPunteros de Filas: ");
    for (int i = 0; i < matriz->filas + 1; i++) {
        printf("%d ", matriz->punterosFilas[i]);
    }
    printf("\n");
}

// Función principal para probar
int main() {
    // Crear dos matrices dispersas de ejemplo
    MatrizDispersa *A = crearMatrizDispersa(4, 4, 6);
    A->valores = (int[]){1, 4, 2, 3, 5, 6};
    A->indicesCol = (int[]){1, 2, 2, 0, 3, 3};
    A->punterosFilas = (int[]){0, 2, 3, 5, 6};

    MatrizDispersa *B = crearMatrizDispersa(4, 4, 6);
    B->valores = (int[]){1, 4, 2, 3, 5, 6};
    B->indicesCol = (int[]){1, 2, 2, 0, 3, 3};
    B->punterosFilas = (int[]){0, 2, 3, 5, 6};

    MatrizDispersa *C = multiplicarMatricesDispersas(A, B);

    imprimirMatrizDispersa(C);

    // Liberar memoria
    liberarMatrizDispersa(A);
    liberarMatrizDispersa(B);
    liberarMatrizDispersa(C);

    return 0;
}
