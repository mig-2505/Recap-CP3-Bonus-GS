// arquivo: temperaturas_busca.c
// Objetivo: comparar busca linear (vetor desordenado) com busca binária (após ordenar)
// Entradas: um valor de temperatura (int) informado pelo usuário
// Saídas: índice encontrado e contadores de iterações em cada técnica
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ----------------------
// Utilidades: impressão
// ----------------------
void imprime_vetor(const int *v, const char dias[][10], int n, const char *titulo) {
    printf("%s [", titulo);
    for (int i = 0; i < n; i++) {
        printf("%s: %d°C%s", dias[i], v[i], (i < n - 1 ? ", " : ""));
    }
    printf("]\n");
}

// -------------------------------------
// Parte A: busca linear + contagem passos
// -------------------------------------
int busca_linear_contando(const int *v, int n, int alvo, int *passos) {
    *passos = 0;
    for (int i = 0; i < n; i++) {
        (*passos)++;                 // conta a comparação v[i] == alvo
        if (v[i] == alvo) return i;  // achou? devolve índice
    }
    return -1;                       // não achou
}

// -------------------------------------
// Ordenação para a parte B (qsort)
// -------------------------------------
int cmp_int(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    // ordem crescente
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

// -------------------------------------
// Parte B: busca binária + contagem passos
// Pressupõe vetor ordenado
// -------------------------------------
int busca_binaria_contando(const int *v, int n, int alvo, int *passos) {
    int ini = 0, fim = n - 1;
    *passos = 0;
    while (ini <= fim) {
        int meio = ini + (fim - ini) / 2; // forma segura contra overflow
        (*passos)++;                      // conta a comparação v[meio] com alvo
        if (v[meio] == alvo) return meio;
        if (v[meio] < alvo) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

int main(void) {
    // -----------------------------
    // Geração de dados (temperaturas diárias)
    // -----------------------------
    const int N = 7;
    int v_desordenado[7];
    const char dias[7][10] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado", "Domingo"};
    srand(42);

    for (int i = 0; i < N; i++) {
        // Temperaturas entre 15 e 35°C (com variações)
        v_desordenado[i] = 15 + rand() % 21;
    }

    // Mostra o vetor desordenado
    imprime_vetor(v_desordenado, dias, N, "Vetor desordenado");

    // -----------------------------
    // Entrada do usuário (alvo)
    // -----------------------------
    int alvo;
    printf("Digite a temperatura a buscar (em °C): ");
    if (scanf("%d", &alvo) != 1) {
        fprintf(stderr, "Entrada invalida.\n");
        return 1;
    }

    // -----------------------------
    // Parte A: busca linear
    // -----------------------------
    int passos_linear = 0;
    int idx_linear = busca_linear_contando(v_desordenado, N, alvo, &passos_linear);
    if (idx_linear == -1) {
        printf("[Linear] Temperatura %d°C NÃO encontrada. Passos = %d\n", alvo, passos_linear);
    } else {
        printf("[Linear] Temperatura %d°C encontrada no dia %s. Passos = %d\n", alvo, dias[idx_linear], passos_linear);
    }

    // -----------------------------
    // Parte B: ordenar + busca binária
    // -----------------------------
    int v_ordenado[7];
    for (int i = 0; i < N; i++) v_ordenado[i] = v_desordenado[i];
    qsort(v_ordenado, N, sizeof(int), cmp_int);

    // Mostra o vetor ordenado
    imprime_vetor(v_ordenado, dias, N, "Vetor ORDENADO");

    int passos_bin = 0;
    int idx_bin = busca_binaria_contando(v_ordenado, N, alvo, &passos_bin);
    if (idx_bin == -1) {
        printf("[Binária] Temperatura %d°C NÃO encontrada. Passos = %d\n", alvo, passos_bin);
    } else {
        printf("[Binária] Temperatura %d°C encontrada no dia %s. Passos = %d\n", alvo, dias[idx_bin], passos_bin);
    }

    // Observação: índices são relativos a cada vetor.
    // O índice da binária refere-se ao vetor ORDENADO.
    return 0;
}