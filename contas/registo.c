#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "registo.h"

// Verificar se o email e a password estão corretos
Conta *login(Conta *inicio, char email[], char pass[])
{
    while (inicio != NULL)
    {
        if (strcmp(inicio->email, email) == 0 && strcmp(inicio->password, pass) == 0)
            return (inicio);
        inicio = inicio->seguinte;
    }
    return (0);
}

// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve o código do último registo + 1 (ou seja, o próximo a ser registado) se existir ou 0 caso contrário
int existeConta(Conta *inicio, int cod)
{
    while (inicio != NULL)
    {
        if (inicio->codigo == cod)
            return (inicio->codigo + 1);
        inicio = inicio->seguinte;
    }
    return (0);
}

// Criar uma nova conta
Conta *inserirConta(Conta *inicio, char email[], char pass[], char nome[], char morada[], char nif[])
{
    int cod = inicio->codigo;
    while (1)
    {
        if (!existeConta(inicio, cod))
        {
            Conta *novo = malloc(sizeof(struct contas));
            if (novo != NULL)
            {
                novo->codigo = cod;
                strcpy(novo->tipo, "cliente");
                strcpy(novo->email, email);
                strcpy(novo->password, pass);
                strcpy(novo->nome, nome);
                strcpy(novo->morada, morada);
                strcpy(novo->nif, nif);
                novo->saldo = 0;
                novo->renting = false;
                novo->seguinte = inicio;
                printf("Conta criada com sucesso!\n");
                return (novo);
            }
            else
            {
                printf("Não foi possível alocar memória\npara criação de um novo utilizador!\n");
                return (inicio);
            }
            break;
        }
        else
            cod++;
    }
}

// inserir conta no ficheiro
Conta *inserirContaFile(Conta *inicio, int cod, char tipo[], char email[], char pass[], char nome[], char morada[], char nif[], float saldo, bool renting)
{
    if (!existeConta(inicio, cod))
    {
        Conta *novo = malloc(sizeof(struct contas));
        if (novo != NULL)
        {
            novo->codigo = cod;
            strcpy(novo->tipo, tipo);
            strcpy(novo->email, email);
            strcpy(novo->password, pass);
            if (strcmp(novo->tipo, "cliente") == 0)
            {
                strcpy(novo->nome, nome);
                strcpy(novo->morada, morada);
                strcpy(novo->nif, nif);
                novo->saldo = saldo;
            }
            else
            {
                strcpy(novo->nome, "n/a");
                strcpy(novo->morada, "n/a");
                strcpy(novo->nif, "n/a");
                novo->saldo = 0;
            }
            novo->renting = false;
            novo->seguinte = inicio;
            return (novo);
        }
        else
        {
            return (inicio);
        }
    }
    else
        return (inicio);
}

// ler contas
Conta *lerConta()
{
    FILE *fp;
    int cod;
    float saldo;
    char tipo[50], email[50], pass[50], nome[50], morada[50], nif[9];
    bool renting;
    Conta *aux = NULL;
    fp = fopen("./storage/contas.txt", "r");
    if (fp != NULL)
    {
        Conta *novo = malloc(sizeof(fp));
        if (novo != NULL)
        {
            //printf("Contas disponíveis:\n");
            while (!feof(fp))
            {
                fscanf(fp, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%f;%d \n", &cod, tipo, email, pass, nome, morada, nif, &saldo, &renting);
                aux = inserirContaFile(aux, cod, tipo, email, pass, nome, morada, nif, saldo, renting);
                novo = aux;
                //printf("%d %s %s %s %s %s %s %.2f %d\n", aux->codigo, aux->tipo, aux->email, aux->password, aux->nome, aux->morada, aux->nif, aux->saldo, aux->renting);
            }
            fclose(fp);
        }
    }
    return (aux);
}

// Remover uma conta a partir do seu código
Conta *removerConta(Conta *inicio, int cod)
{
    Conta *anterior = inicio, *atual = inicio, *aux;
    if (atual == NULL)
    {
        printf("Não existem contas registadas!\n");
        return 0;
    }
    else if (atual->codigo == cod) // remoção do 1º registo
    {
        aux = atual->seguinte;
        free(atual);
        return aux;
    }
    else
    {
        while ((atual != NULL) && (atual->codigo != cod))
        {
            anterior = atual;
            atual = atual->seguinte;
        }
        if (atual == NULL)
        {
            printf("Conta não encontrada!\n");
            return 0;
        }
        else
        {
            anterior->seguinte = atual->seguinte;
            free(atual);
            return inicio;
        }
    }
}

// guardar contas no ficheiro
void guardarContas(Conta *inicio)
{
    FILE *fp;
    fp = fopen("./storage/contas.txt", "w");
    if (fp != NULL)
    {
        Conta *aux = inicio;
        if (aux != NULL)
        {
            while (aux != NULL)
            {
                fprintf(fp, "%d;%s;%s;%s;%s;%s;%s;%f;%d\n", aux->codigo, aux->tipo, aux->email, aux->password, aux->nome, aux->morada, aux->nif, aux->saldo, aux->renting);
                aux = aux->seguinte;
            }
        }
        fclose(fp);
        printf("Guardado no ficheiro com sucesso!\n");
    }
    else
        printf("O ficheiro contas.txt não existe!\n");
}

void listarContas(Conta *conta)
{
    printf("\n-- LISTA DE CLIENTES ------------------\n");
    printf("---------------------------------------\n");
    printf("| ID | Nome         | Saldo | Aluguer |\n");
    printf("---------------------------------------\n");
    while (conta != NULL)
    {
        if (!strcmp(conta->tipo,"cliente"))
        {
            printf("| %-2d | %-12s | %05.2f | %-7d |\n", conta->codigo, conta->nome, conta->saldo, conta->renting);
        }
        conta = conta->seguinte;
    }
    printf("---------------------------------------\n");
}