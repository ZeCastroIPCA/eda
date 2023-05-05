#pragma once
#include <stdio.h>
#include "../../meios/meio.h"

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
    struct contas *seguinte;
} Conta;

void listarContas(Conta *contas, char tipo[]);
void alterarConta(Conta *contas);
void removerConta(Conta *contas, int cod, int who);
void alugarMeio(Conta *contas, Conta *conta, Meio *meios);
void carregarSaldo(Conta *conta);

Conta *existeConta(Conta *contas, int cod);
int verificarEmail(Conta *contas, char email[]);

Conta *lerContas();
void guardarContas(Conta *contas);