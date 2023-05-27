#pragma once
#include <stdio.h>

typedef struct meios Meio;
typedef struct grafos Grafo;

typedef struct contas
{
    int codigo; // código da conta
    char tipo[50]; // tipo de conta: cliente ou gestor
    char email[50]; // email do cliente ou gestor
    char password[50]; // password do cliente ou gestor
    char nome[50]; // nome do cliente
    char morada[50]; // morada do cliente
    char nif[9]; // nif do cliente
    float saldo; // saldo da conta do cliente
    int meio_id; // id do meio de mobilidade elétrica alugado pelo cliente
    char localizacao[100]; // localização do cliente
    struct contas *seguinte;
} Conta;

void listarContas(Conta *contas, char tipo[]); // listar na consola o conteúdo da lista ligada contas
void alterarConta(Conta *contas, Grafo *grafo); // Alterar uma conta a partir do seu código
void removerConta(Conta *contas, int cod, int who); // Remover uma conta a partir do seu código
void alugarMeio(Conta *contas, Conta *conta, Meio *meios, Grafo *grafo); // Alugar um meio de mobilidade elétrica
void carregarSaldo(Conta *conta); // Carregar saldo na conta

Conta *existeConta(Conta *contas, int cod); // Determinar existência do 'codigo' na lista ligada 'contas'
int verificarEmail(Conta *contas, char email[]); // Determinar existência do 'email' na lista ligada 'contas'

Conta *lerContas(); // Ler as contas de um ficheiro
void guardarContas(Conta *contas); // Guardar as contas num ficheiro