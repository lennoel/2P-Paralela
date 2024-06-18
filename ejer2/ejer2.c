#include <stdio.h>
#include <stdlib.h>

// estructura para la matriz dispersa en formato csr
typedef struct {
    int *values;      // valores no cero
    int *col_indices; // indices de columna de los valores
    int *row_ptr;     // punteros a las filas en el array de valores
    int num_rows;     // numero de filas
    int num_cols;     // numero de columnas
    int num_nonzeros; // numero de elementos no cero
} SparseMatrix;
// funcion para contar el numero de elementos no cero en un grafico
int count_nonzeros(int **graph, int num_nodes) {
    int count = 0;
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (graph[i][j] != 0) {
                count++;
            }
        }
    }
    return count;
}

// funcion para convertir un grafico a una matriz dispersa csr
SparseMatrix* graph_to_sparse(int **graph, int num_nodes) {
    SparseMatrix *sparse_matrix = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    sparse_matrix->num_rows = num_nodes;
    sparse_matrix->num_cols = num_nodes;
    sparse_matrix->num_nonzeros = count_nonzeros(graph, num_nodes);

    sparse_matrix->values = (int*)malloc(sparse_matrix->num_nonzeros * sizeof(int));
    sparse_matrix->col_indices = (int*)malloc(sparse_matrix->num_nonzeros * sizeof(int));
    sparse_matrix->row_ptr = (int*)malloc((num_nodes + 1) * sizeof(int));

    int k = 0;
    sparse_matrix->row_ptr[0] = 0;

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (graph[i][j] != 0) {
                sparse_matrix->values[k] = graph[i][j];
                sparse_matrix->col_indices[k] = j;
                k++;
            }
        }
        sparse_matrix->row_ptr[i + 1] = k;
    }

    return sparse_matrix;
}
// funcion para imprimir una matriz dispersa csr
void print_sparse_matrix(SparseMatrix *sparse_matrix) {
    printf("valores: ");
    for (int i = 0; i < sparse_matrix->num_nonzeros; i++) {
        printf("%d ", sparse_matrix->values[i]);
    }
    printf("\n");

    printf("indices de columnas: ");
    for (int i = 0; i < sparse_matrix->num_nonzeros; i++) {
        printf("%d ", sparse_matrix->col_indices[i]);
    }
    printf("\n");

    printf("punteros a filas: ");
    for (int i = 0; i <= sparse_matrix->num_rows; i++) {
        printf("%d ", sparse_matrix->row_ptr[i]);
    }
    printf("\n");
}
int main() {
    // ejemplo de grafico 1 representado por una matriz de adyacencia
    int *graph1[] = {
        (int[]){0, 1, 0, 0},
        (int[]){1, 0, 1, 0},
        (int[]){0, 1, 0, 1},
        (int[]){0, 0, 1, 0}
    };
    int num_nodes1 = 4;

    // ejemplo de grafico 2 representado por una matriz de adyacencia
    int *graph2[] = {
        (int[]){0, 2, 0, 0},
        (int[]){2, 0, 3, 0},
        (int[]){0, 3, 0, 4},
        (int[]){0, 0, 4, 0}
    };
    int num_nodes2 = 4;

    // convertir los graficos a matrices dispersas csr
    SparseMatrix *sparse_matrix1 = graph_to_sparse(graph1, num_nodes1);
    SparseMatrix *sparse_matrix2 = graph_to_sparse(graph2, num_nodes2);

    // imprimir las matrices dispersas
    printf("matriz dispersa para grafico 1:\n");
    print_sparse_matrix(sparse_matrix1);

    printf("matriz dispersa para grafico 2:\n");
    print_sparse_matrix(sparse_matrix2);

    // liberar memoria
    free(sparse_matrix1->values);
    free(sparse_matrix1->col_indices);
    free(sparse_matrix1->row_ptr);
    free(sparse_matrix1);

    free(sparse_matrix2->values);
    free(sparse_matrix2->col_indices);
    free(sparse_matrix2->row_ptr);
    free(sparse_matrix2);

    return 0;
}
