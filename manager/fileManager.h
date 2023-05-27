#pragma once
#include <stdio.h>
#include <time.h>

typedef struct contas Conta;
typedef struct meios Meio;
typedef struct grafos Grafo;

// inserir conta no ficheiro
Conta *inserirContaFile(Conta *inicio, int cod, char tipo[], char email[], char pass[], char nome[], char morada[], char nif[], float saldo, int meio_id, char localizacao[]);

// inserir meio no ficheiro 
Meio *inserirMeioFile(Meio *meios, int cod, char tipo[], float bateria, float autonomia, int id_cliente, float custo, time_t inicio_aluguer);

// inserir grafo no ficheiro
Grafo *inserirGrafoFile(Grafo *grafo, char veritice[], char adjacente[], float peso, int codMeio);