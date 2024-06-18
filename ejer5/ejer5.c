#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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
// Función para multiplicar dos matrices dispersas en paralelo utilizando OpenMP
MatrizDispersa* multiplicarMatricesDispersasParalelo(MatrizDispersa *A, MatrizDispersa *B, int numThreads) {
    if (A->columnas != B->filas) {
        fprintf(stderr, "Error: Las matrices no se pueden multiplicar debido a dimensiones incompatibles.\n");
        exit(EXIT_FAILURE);
    }

    // Estimación inicial del tamaño de la matriz resultado
    int noCerosEstimados = A->noCeros * B->noCeros;
    MatrizDispersa *C = crearMatrizDispersa(A->filas, B->columnas, noCerosEstimados);

    // Inicializar punteros de filas para la matriz resultado
    #pragma omp parallel for num_threads(numThreads)
    for (int i = 0; i <= A->filas; i++) {
        C->punterosFilas[i] = 0;
    }

    // Multiplicar matrices en paralelo
    #pragma omp parallel for num_threads(numThreads)
    for (int i = 0; i < A->filas; i++) {
        for (int j = A->punterosFilas[i]; j < A->punterosFilas[i + 1]; j++) {
            int colA = A->indicesCol[j];
            int valA = A->valores[j];

            for (int k = B->punterosFilas[colA]; k < B->punterosFilas[colA + 1]; k++) {
                int colB = B->indicesCol[k];
                int valB = B->valores[k];

                #pragma omp atomic
                C->valores[i * B->columnas + colB] += valA * valB;
            }
        }
    }

    // Construir punteros de filas para la matriz resultado
    int totalNoCeros = 0;
    for (int i = 0; i < C->filas; i++) {
        C->punterosFilas[i] = totalNoCeros;
        for (int j = 0; j < C->columnas; j++) {
            if (C->valores[i * C->columnas + j] != 0) {
                C->indicesCol[totalNoCeros] = j;
                C->valores[totalNoCeros] = C->valores[i * C->columnas + j];
                totalNoCeros++;
            }
        }
    }
    C->punterosFilas[C->filas] = totalNoCeros;
    C->noCeros = totalNoCeros;

    return C;
}
int main() {
    int numFilas = 1000;
    int numColumnas = 1000;
    int noCerosA = 5000;
    int noCerosB = 5000;

    // Crear dos matrices dispersas de ejemplo
    MatrizDispersa *A = crearMatrizDispersa(numFilas, numColumnas, noCerosA);
    MatrizDispersa *B = crearMatrizDispersa(numFilas, numColumnas, noCerosB);

    // Rellenar matrices con valores aleatorios (esto es solo un ejemplo)
    for (int i = 0; i < noCerosA; i++) {
        A->valores[i] = rand() % 10;
        A->indicesCol[i] = rand() % numColumnas;
    }
    for (int i = 0; i < noCerosB; i++) {
        B->valores[i] = rand() % 10;
        B->indicesCol[i] = rand() % numColumnas;
    }
    for (int i = 0; i <= numFilas; i++) {
        A->punterosFilas[i] = rand() % noCerosA;
        B->punterosFilas[i] = rand() % noCerosB;
    }

    // Multiplicar matrices en paralelo
    int numThreads = 4;
    MatrizDispersa *C = multiplicarMatricesDispersasParalelo(A, B, numThreads);

    // Imprimir algunos elementos de la matriz resultante
    imprimirMatrizDispersa(C);

    // Liberar memoria
    liberarMatrizDispersa(A);
    liberarMatrizDispersa(B);
    liberarMatrizDispersa(C);

    return 0;
}
