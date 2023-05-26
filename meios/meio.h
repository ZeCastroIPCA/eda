#pragma once
#include <stdio.h>
#include <time.h>

typedef struct grafos Grafo;

typedef struct meios
{
    int codigo; // código do meio de mobilidade elétrica
    char tipo[50];
    float bateria;
    float autonomia;
    int id_cliente;
    float custo;
    time_t inicio_aluguer;
    struct meios *seguinte;
} Meio;

void inserirMeio(Meio **meios, Grafo **grafo); // Inserir meio de transporte e adicionar localização com geocódigo no grafo
void listarMeios(Meio *meios); // listar na consola o conteúdo da lista ligada meios
void listarMeiosParaCliente(Meio *meios); // listar todos os meios disponíveis para aluguer por ordem descrescente de autonomia
void listarMeiosPorGeoCode(Grafo *grafo); // listar os meios numa determinada localização
void alterarMeio(Meio *meios, Grafo *grafo); // Alterar um meio a partir do seu código 
void removerMeio(Meio *meios); // Remover um meio a partir do seu código

Meio *existeMeio(Meio *meios, int codigo); // Determinar existência do 'codigo' na lista ligada 'meios'

Meio *lerMeios(); // Ler os meios de um ficheiro
void guardarMeios(Meio *meios); // Guardar os meios num ficheiro
