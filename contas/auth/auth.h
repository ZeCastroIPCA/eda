#pragma once
#include <stdio.h>

typedef struct grafos Grafo;
typedef struct contas Conta;
typedef struct meios Meio;

void handleLogin(Conta *contas, Meio *meios, Grafo *grafo);
void handleRegisto(Conta *contas, int who);

Conta *login(Conta *contas, char email[], char pass[]);
void registo(Conta *contas, char email[], char pass[], char nome[], char morada[], char nif[], char tipo[]);