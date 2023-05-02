#pragma once
#include <stdio.h>

typedef struct registo
{
    int codigo; // código do meio de mobilidade elétrica
    char tipo[50];
    float bateria;
    float autonomia;
    int idCliente;
    float custo;
    int disponivel;
    char geoCode[100];
    struct registo *seguinte;
} Meio;

Meio *inserirMeio(Meio *inicio, int cod, char tipo[], float bat, float aut); // Inserção de um novo registo
void listarMeios(Meio *inicio);                                              // listar na consola o conteúdo da lista ligada
int existeMeio(Meio *inicio, int codigo);                                    // Determinar existência do 'codigo' na lista ligada 'inicio'
void removerMeio(Meio *inicio, int cod);                                    // Remover um meio a partir do seu código

int guardarMeios(Meio *inicio);
Meio *lerMeios();
