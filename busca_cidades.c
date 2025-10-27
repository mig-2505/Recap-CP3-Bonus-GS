// arquivo: busca_cidades.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Comparação case-insensitive (compatível com todos os sistemas)
int stricmp_custom(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = tolower((unsigned char)*s1);
        char c2 = tolower((unsigned char)*s2);
        if (c1 != c2) return c1 - c2;
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int busca_linear_cidades(const char* cidades[], int n, const char* alvo) {
    for (int i = 0; i < n; i++) {
        if (stricmp_custom(cidades[i], alvo) == 0) return i;
    }
    return -1;
}

int busca_binaria_cidades(const char* cidades[], int n, const char* alvo) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = ini + (fim - ini) / 2;
        int cmp = stricmp_custom(cidades[meio], alvo);
        if (cmp == 0) return meio;
        if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int main() {
    const char* cidades_ordenados[] = {
        "Curitiba", "Fortaleza", "Manaus", "Recife", "Salvador"
    };
    const char* cidades_nao_ordenados[] = {
        "Recife", "Curitiba", "Salvador", "Fortaleza", "Manaus"
    };

    int n = 5;
    char alvo[50];

    printf("Digite a cidade a buscar: ");
    scanf("%49s", alvo);

    // Busca linear (vetor não ordenado)
    int idx_linear = busca_linear_cidades(cidades_nao_ordenados, n, alvo);
    if (idx_linear == -1)
        printf("[Linear] Cidade '%s' NAO encontrada (vetor NAO ordenado).\n", alvo);
    else
        printf("[Linear] Cidade '%s' encontrada no indice %d (vetor NAO ordenado).\n", alvo, idx_linear);

    // Busca binária (vetor ordenado)
    int idx_bin = busca_binaria_cidades(cidades_ordenados, n, alvo);
    if (idx_bin == -1)
        printf("[Binaria] Cidade '%s' NAO encontrada (vetor ORDENADO).\n", alvo);
    else
        printf("[Binaria] Cidade '%s' encontrada no indice %d (vetor ORDENADO).\n", alvo, idx_bin);

    return 0;
}
