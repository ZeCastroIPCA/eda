#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct alugueres
{
    int id_aluguer; // código do aluguer
    int id_meio;    // código do meio
    int id_cliente; // código do cliente
    float tempo;      // tempo de aluguer em minutos
    struct alugueres *seguinte;
} Aluguer;

void inserirAluguer(Aluguer *inicio, int id_meio, int id_cliente, float tempo); // Inserção de um novo registo
Aluguer *inserirAluguerFile(Aluguer *inicio, int id_aluguer, int id_meio, int id_cliente, float tempo); // Inserção de um novo registo no ficheiro
void listarAluguer(Aluguer *inicio);                                              // listar na consola o conteúdo da lista ligada
int existeAluguer(Aluguer *inicio, int id_aluguer);                                    // Determinar existência do 'codigo' na lista ligada 'inicio'
Aluguer *removerAluguer(Aluguer *inicio, int id_aluguer);                                    // Remover uma Aluguer a partir do seu código

int guardarAluguer(Aluguer *inicio);
Aluguer *lerAluguer();