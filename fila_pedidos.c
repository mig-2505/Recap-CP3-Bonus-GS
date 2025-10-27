#include <stdio.h>
#include <string.h>

#define MAX 5  // Tamanho máximo da fila

// Estrutura para representar um pedido
typedef struct {
    int numeroPedido;
    char nomeCliente[100];
} Pedido;

// Fila de pedidos
Pedido fila[MAX];
int inicio = 0, fim = -1, qtd = 0;

// Função para enfileirar um pedido
void enfileirar(int numeroPedido, const char *nomeCliente) {
    if (qtd == MAX) {
        printf("Fila cheia! Não é possível adicionar mais pedidos.\n");
        return;
    }
    fim = (fim + 1) % MAX;
    fila[fim].numeroPedido = numeroPedido;
    strncpy(fila[fim].nomeCliente, nomeCliente, sizeof(fila[fim].nomeCliente) - 1);
    fila[fim].nomeCliente[sizeof(fila[fim].nomeCliente) - 1] = '\0';  // Garantir que a string está terminada
    qtd++;
}

// Função para desenfileirar (atender) o pedido
Pedido desenfileirar() {
    if (qtd == 0) {
        printf("Fila vazia! Não há pedidos para atender.\n");
        Pedido vazio = {-1, ""};  // Retorna um pedido vazio em caso de fila vazia
        return vazio;
    }
    Pedido pedidoAtendido = fila[inicio];
    inicio = (inicio + 1) % MAX;
    qtd--;
    return pedidoAtendido;
}

// Função para mostrar o estado atual da fila
void mostrarFila() {
    if (qtd == 0) {
        printf("Fila vazia! Nenhum pedido para atender.\n");
        return;
    }
    printf("Pedidos na fila:\n");
    for (int i = 0; i < qtd; i++) {
        int idx = (inicio + i) % MAX;
        printf("Pedido nº %d | Cliente: %s\n", fila[idx].numeroPedido, fila[idx].nomeCliente);
    }
}

int main() {
    // Testando as funções de enfileirar, desenfileirar e mostrar estado

    // Enfileirando pedidos
    enfileirar(101, "Carlos");
    enfileirar(102, "Maria");
    enfileirar(103, "João");
    mostrarFila();  // Exibe os pedidos na fila

    // Atendendo (desenfileirando) o primeiro pedido
    Pedido atendido = desenfileirar();
    if (atendido.numeroPedido != -1) {
        printf("\nPedido atendido: Pedido nº %d | Cliente: %s\n", atendido.numeroPedido, atendido.nomeCliente);
    }
    mostrarFila();  // Exibe a fila após o atendimento

    // Adicionando mais pedidos
    enfileirar(104, "Ana");
    enfileirar(105, "Roberto");
    mostrarFila();  // Exibe a fila após os novos pedidos

    // Tentando adicionar um pedido quando a fila está cheia
    enfileirar(106, "Luana");

    // Atendendo mais um pedido
    atendido = desenfileirar();
    if (atendido.numeroPedido != -1) {
        printf("\nPedido atendido: Pedido nº %d | Cliente: %s\n", atendido.numeroPedido, atendido.nomeCliente);
    }
    mostrarFila();  // Exibe a fila após mais um atendimento

    return 0;
}
