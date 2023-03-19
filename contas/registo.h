#pragma once
#include <stdio.h>
#include <stdbool.h>

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
    bool renting; // estado do renting do cliente
    struct contas *seguinte;
} Conta;

Conta *login(Conta *inicio, char email[], char pass[]); // Verificar se o email e a password estão corretos e se o utilizador é um cliente ou gestor
Conta *inserirConta(Conta *inicio, char email[], char pass[], char nome[], char morada[], char nif[]); // Inserção de um novo registo
Conta *inserirContaFile(Conta *inicio, int cod, char tipo[], char email[], char pass[], char nome[], char morada[], char nif[], float saldo, bool renting); // Inserção de um novo registo no ficheiro
void listarContas(Conta *inicio);                                              // listar na consola o conteúdo da lista ligada
int existeConta(Conta *inicio, int codigo);                                    // Determinar existência do 'codigo' na lista ligada 'inicio'
Conta *removerConta(Conta *inicio, int cod);                                    // Remover uma conta a partir do seu código

void guardarContas(Conta *inicio);
Conta *lerConta();