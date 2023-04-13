#pragma once
#include <stdio.h>

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
    int meio_id; // id do meio associado ao cliente
    struct contas *seguinte;
} Conta;

void removerConta(Conta *contas, int cod);
void alterarConta(Conta *contas, int cod);
Conta *lerContas();
void guardarContas(Conta *contas);
void listarContas(Conta *contas);
int existeConta(Conta *contas, int cod);
int verifyEmail(Conta *contas, char email[]);