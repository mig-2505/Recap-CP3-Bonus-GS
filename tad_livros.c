// tad_livros.c
#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 100  // Tamanho máximo do vetor de livros

// Definindo a estrutura Livro
typedef struct {
    char titulo[100];
    char autor[100];
    int ano;
} Livro;

// Função para criar um livro
Livro criarLivro(const char *titulo, const char *autor, int ano) {
    Livro livro;
    strncpy(livro.titulo, titulo, sizeof(livro.titulo));
    strncpy(livro.autor, autor, sizeof(livro.autor));
    livro.ano = ano;
    return livro;
}

// Função para adicionar um livro ao vetor de livros
void adicionarLivro(Livro livros[], int *numLivros, Livro livro) {
    if (*numLivros < MAX_LIVROS) {
        livros[*numLivros] = livro;
        (*numLivros)++;
    } else {
        printf("Erro: Não é possível adicionar mais livros, limite atingido.\n");
    }
}

// Função para buscar um livro pelo título
int buscarLivroPorTitulo(Livro livros[], int numLivros, const char *titulo) {
    for (int i = 0; i < numLivros; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0) {
            return i;  // Retorna o índice do livro encontrado
        }
    }
    return -1;  // Retorna -1 se não encontrar
}

// Função para listar todos os livros
void listarLivros(Livro livros[], int numLivros) {
    if (numLivros == 0) {
        printf("Nenhum livro registrado.\n");
    } else {
        for (int i = 0; i < numLivros; i++) {
            printf("Livro %d: %s | Autor: %s | Ano: %d\n", i + 1, livros[i].titulo, livros[i].autor, livros[i].ano);
        }
    }
}

int main() {
    Livro livros[MAX_LIVROS];  // Vetor para armazenar os livros
    int numLivros = 0;  // Contador de livros cadastrados

    // Criando livros e adicionando ao vetor
    Livro livro1 = criarLivro("O Senhor dos Anéis", "J.R.R. Tolkien", 1954);
    adicionarLivro(livros, &numLivros, livro1);

    Livro livro2 = criarLivro("1984", "George Orwell", 1949);
    adicionarLivro(livros, &numLivros, livro2);

    Livro livro3 = criarLivro("A Revolução dos Bichos", "George Orwell", 1945);
    adicionarLivro(livros, &numLivros, livro3);

    // Listar todos os livros
    printf("Livros cadastrados:\n");
    listarLivros(livros, numLivros);

    // Buscar um livro pelo título
    char tituloBusca[100];
    printf("\nDigite o título do livro para buscar: ");
    fgets(tituloBusca, sizeof(tituloBusca), stdin);
    tituloBusca[strcspn(tituloBusca, "\n")] = '\0';  // Remover o '\n' do final da string

    int idx = buscarLivroPorTitulo(livros, numLivros, tituloBusca);
    if (idx != -1) {
        printf("\nLivro encontrado:\n");
        printf("Título: %s | Autor: %s | Ano: %d\n", livros[idx].titulo, livros[idx].autor, livros[idx].ano);
    } else {
        printf("Livro não encontrado.\n");
    }

    return 0;
}