#pragma once
#include <stdio.h>
#include <time.h>

typedef struct meios
{
    int codigo; // código do meio de mobilidade elétrica
    char tipo[50];
    float bateria;
    float autonomia;
    int id_cliente;
    float custo;
    time_t inicio_aluguer;
    char geoCode[100];
    struct meios *seguinte;
} Meio;

void inserirMeio(Meio *meios); // Inserção de um novo meio
void listarMeios(Meio *meios); // listar na consola o conteúdo da lista ligada meios
void listarMeiosParaCliente(Meio *meios); // listar todos os meios disponíveis para aluguer
void alterarMeio(Meio *meios, int cod); // Alterar um meio a partir do seu código 
void removerMeio(Meio *meios, int cod); // Remover um meio a partir do seu código

Meio *existeMeio(Meio *meios, int codigo); // Determinar existência do 'codigo' na lista ligada 'meios'

Meio *lerMeios();
void guardarMeios(Meio *meios);
