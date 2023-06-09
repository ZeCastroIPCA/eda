#pragma once
#include <stdio.h>

typedef struct grafos Grafo;
typedef struct contas Conta;
typedef struct meios Meio;

void menuGestorMeios(Meio *meios, Grafo *grafo);
void menuGestorContas(Conta *contas, Grafo *grafo);
void menuGestorGrafo(Grafo *grafo, Meio *meios);
void menuGestorPrincipal(Conta *conta, Meio *meios, Grafo *grafo);
void menuPrincipal(Conta *conta, Meio *meios, Grafo *grafo);
void menuCliente(Conta *contas, Conta *conta, Meio *meios, Grafo *grafo);
