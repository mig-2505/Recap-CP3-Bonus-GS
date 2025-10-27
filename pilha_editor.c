#include <stdio.h>
#include <string.h>

#define MAX 10
#define TEXTO_MAX 100

typedef struct {
    char acao[10];   
    char texto[TEXTO_MAX];
} Operacao;

Operacao pilha[MAX];
int topo = -1;
char buffer[TEXTO_MAX] = "";

// Operações básicas da pilha
void push(Operacao op) {
    if (topo == MAX - 1) {
        printf("Histórico cheio!\n");
        return;
    }
    pilha[++topo] = op;
}

Operacao pop() {
    Operacao vazio = {"", ""};
    if (topo == -1) {
        printf("Nada para desfazer.\n");
        return vazio;
    }
    return pilha[topo--];
}

// Mostra o histórico
void mostrarHistorico() {
    if (topo == -1) {
        printf("Histórico vazio.\n");
        return;
    }
    printf("Histórico de ações:\n");
    for (int i = topo; i >= 0; i--) {
        printf(" %d) %s \"%s\"\n", i + 1, pilha[i].acao, pilha[i].texto);
    }
}

// Mostra o texto atual
void mostrarTexto() {
    printf("Texto atual: \"%s\"\n", buffer);
}

// Executa uma ação e salva na pilha 
void inserir(const char *texto) {
    strcat(buffer, texto);
    Operacao op = {"INSERIR", ""};
    strcpy(op.texto, texto);
    push(op);
    printf("Inserido: \"%s\"\n", texto);
}

void apagar(int n) {
    int len = strlen(buffer);
    if (n > len) n = len;
    char removido[TEXTO_MAX];
    strcpy(removido, buffer + len - n);
    buffer[len - n] = '\0';

    Operacao op = {"APAGAR", ""};
    strcpy(op.texto, removido);
    push(op);
    printf("Apagado: \"%s\"\n", removido);
}

void colar(const char *texto) {
    strcat(buffer, texto);
    Operacao op = {"COLAR", ""};
    strcpy(op.texto, texto);
    push(op);
    printf("Colado: \"%s\"\n", texto);
}

// Desfaz a última ação
void desfazer() {
    Operacao op = pop();
    if (strcmp(op.acao, "") == 0) return;

    if (strcmp(op.acao, "INSERIR") == 0 || strcmp(op.acao, "COLAR") == 0) {
        int len = strlen(op.texto);
        buffer[strlen(buffer) - len] = '\0';
        printf("Desfeito: %s \"%s\"\n", op.acao, op.texto);
    } 
    else if (strcmp(op.acao, "APAGAR") == 0) {
        strcat(buffer, op.texto);
        printf("Desfeito: APAGAR \"%s\"\n", op.texto);
    }
    mostrarTexto();
}

// Programa principal
int main() {
    inserir("Ola");
    colar(", mundo!");
    mostrarTexto();

    apagar(6);
    mostrarTexto();

    printf("\n--- Histórico ---\n");
    mostrarHistorico();

    printf("\n--- Desfazendo ações ---\n");
    desfazer();
    desfazer();
    desfazer();
    desfazer(); 

    return 0;
}