#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_CLIENTES 100

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

struct Cliente {
    int numeroConta;
    char nome[50];
    double saldo;
    int ativo; 
};

#define COR_SUCESSO 2 
#define COR_LETRAS_AZUIS 9  
#define COR_FUND0_BRANCO 240

void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void cadastrarCliente(struct Cliente *clientes, int *quantidadeClientes, int *numeroContaAtual) {
    if (*quantidadeClientes < MAX_CLIENTES) {
        setTextColor(COR_LETRAS_AZUIS | COR_FUND0_BRANCO);
        printf("Digite o nome do cliente: ");
        limparBuffer();

        fgets(clientes[*quantidadeClientes].nome, sizeof(clientes[*quantidadeClientes].nome), stdin);
        clientes[*quantidadeClientes].nome[strcspn(clientes[*quantidadeClientes].nome, "\n")] = '\0';

        clientes[*quantidadeClientes].numeroConta = (*numeroContaAtual)++;
        clientes[*quantidadeClientes].saldo = 0.0;
        clientes[*quantidadeClientes].ativo = 1;

        (*quantidadeClientes)++;

        setTextColor(COR_LETRAS_AZUIS | COR_FUND0_BRANCO);
        printf("Cliente cadastrado com sucesso.\nNumero da conta: %d\n", clientes[*quantidadeClientes - 1].numeroConta);
        setTextColor(COR_FUND0_BRANCO);
    } else {
        printf("Limite maximo de clientes atingido.\n");
    }
    setTextColor(COR_FUND0_BRANCO); 
}

int encontrarCliente(struct Cliente *clientes, int quantidadeClientes, int numeroConta) {
    int i = 0;
    while (i < quantidadeClientes && clientes[i].numeroConta != numeroConta) {
        i++;
    }

    if (i < quantidadeClientes && clientes[i].ativo) {
        return i;
    } else {
        return -1;
    }
}

void realizarDeposito(struct Cliente *clientes, int quantidadeClientes) {
    int numeroConta;
    double valor;

    printf("Digite o numero da conta: ");
    scanf("%d", &numeroConta);

    int indiceCliente = encontrarCliente(clientes, quantidadeClientes, numeroConta);

    if (indiceCliente != -1) {
        printf("Digite o valor do deposito: ");
        scanf("%lf", &valor);

        if (valor > 0) {
            clientes[indiceCliente].saldo += valor;
            setTextColor(COR_LETRAS_AZUIS | COR_FUND0_BRANCO);
            printf("Deposito realizado com sucesso.\nNovo saldo: %.2f\n", clientes[indiceCliente].saldo);
            setTextColor(COR_FUND0_BRANCO);
        } else {
            printf("Valor do deposito deve ser maior que zero.\n");
        }
    } else {
        printf("Conta nao encontrada ou encerrada.\n");
    }
}

void realizarLevantamento(struct Cliente *clientes, int quantidadeClientes) {
    int numeroConta;
    double valor;

    printf("Digite o numero da conta: ");
    scanf("%d", &numeroConta);

    int indiceCliente = encontrarCliente(clientes, quantidadeClientes, numeroConta);

    if (indiceCliente != -1) {
        printf("Digite o valor do levantamento: ");
        scanf("%lf", &valor);

        if (valor > 0 && valor <= clientes[indiceCliente].saldo) {
            clientes[indiceCliente].saldo -= valor;
            setTextColor(COR_LETRAS_AZUIS | COR_FUND0_BRANCO);
            printf("Levantamento realizado com sucesso.\nNovo saldo: %.2f\n", clientes[indiceCliente].saldo);
            setTextColor(COR_FUND0_BRANCO);
        } else {
            printf("Valor invalido ou saldo insuficiente.\n");
        }
    } else {
        printf("Conta nao encontrada ou encerrada.\n");
    }
}

void consultarSaldo(struct Cliente *clientes, int quantidadeClientes) {
    int numeroConta;

    printf("Digite o numero da conta: ");
    scanf("%d", &numeroConta);

    int indiceCliente = encontrarCliente(clientes, quantidadeClientes, numeroConta);

    if (indiceCliente != -1) {
        setTextColor(COR_LETRAS_AZUIS | COR_FUND0_BRANCO);
        printf("Saldo atual: %.2f\n", clientes[indiceCliente].saldo);
        setTextColor(COR_FUND0_BRANCO);
    } else {
        printf("Conta nao encontrada ou encerrada.\n");
    }
}

void encerrarConta(struct Cliente *clientes, int *quantidadeClientes) {
    int numeroConta;
    char resposta;

    printf("Digite o numero da conta a ser encerrada: ");
    scanf("%d", &numeroConta);

    int indiceCliente = encontrarCliente(clientes, *quantidadeClientes, numeroConta);

    if (indiceCliente != -1) {
        printf("Tem certeza que deseja encerrar a conta? (S/N): ");
        scanf(" %c", &resposta);

        if (resposta == 'S' || resposta == 's') {
            clientes[indiceCliente].ativo = 0;
            setTextColor(COR_LETRAS_AZUIS | COR_FUND0_BRANCO);
            printf("Conta encerrada com sucesso.\n");
            setTextColor(COR_FUND0_BRANCO);
        } else {
            printf("Encerramento da conta cancelado.\n");
        }
    } else {
        printf("Conta nao encontrada ou ja encerrada.\n");
    }
}

int main() {
    system("color F0");
    struct Cliente clientes[MAX_CLIENTES];
    int quantidadeClientes = 0;
    int numeroContaAtual = 1;

    int escolha;

    do {
        setTextColor(COR_LETRAS_AZUIS | COR_FUND0_BRANCO);
        printf("|==========MENU==========|\n");
        printf("|1. Cadastrar Cliente    |\n");
        printf("|2. Realizar Deposito    |\n");
        printf("|3. Realizar Levantamento|\n");
        printf("|4. Consultar Saldo      |\n");
        printf("|5. Encerrar Conta       |\n");
        printf("|0. Sair                 |\n");
        printf("|========================|\n");
        printf("Digite sua escolha: ");
        setTextColor(COR_FUND0_BRANCO);

        while (1) {
            scanf("%d", &escolha);

            if (escolha >= 0 && escolha <= 5) {
                break;
            } else {
                setTextColor(COR_SUCESSO);
                printf("Escolha invalida. Por favor, tente novamente.\n");
                setTextColor(COR_LETRAS_AZUIS | COR_FUND0_BRANCO);
                printf("Digite sua escolha: ");
                setTextColor(COR_FUND0_BRANCO);
            }
        }

        switch (escolha) {
            case 1:
                cadastrarCliente(clientes, &quantidadeClientes, &numeroContaAtual);
                break;
            case 2:
                realizarDeposito(clientes, quantidadeClientes);
                break;
            case 3:
                realizarLevantamento(clientes, quantidadeClientes);
                break;
            case 4:
                consultarSaldo(clientes, quantidadeClientes);
                break;
            case 5:
                encerrarConta(clientes, &quantidadeClientes);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Escolha invalida. Encerrando o programa.\n");
                break;
        }
    } while (escolha != 0);

    return 0;
}
