#pragma once
#include <stdio.h>
#include <time.h>

typedef struct contas Conta;
typedef struct meios Meio;

// inserir conta no ficheiro
Conta *inserirContaFile(Conta *inicio, int cod, char tipo[], char email[], char pass[], char nome[], char morada[], char nif[], float saldo, int meio_id);

// inserir meio no ficheiro 
Meio *inserirMeioFile(Meio *meios, int cod, char tipo[], float bateria, float autonomia, int id_cliente, float custo, time_t inicio_aluguer);