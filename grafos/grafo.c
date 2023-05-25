#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo.h"
#include "../meios/meio.h"

// guarda o grafo em ficheiros de texto e binário
// void guardarGrafo(Grafo *grafo)
// {
//     FILE *fp, *fpb;
//     fp = fopen("./storage/grafo.txt", "w+");
//     fpb = fopen("./storage/grafo.bin", "wb+");
//     if (fp != NULL && fpb != NULL)
//     {
//         Grafo *aux = grafo;
//         if (aux != NULL)
//         {
//             while (aux != NULL)
//             {
//                 fprintf(fp, "%s;%s;%f;%d\n", aux->vertice, aux->adjacentes->vertice, aux->adjacentes->peso, aux->meios->codigo);
//                 fprintf(fp, "%s;%s;%f;%d\n", aux->vertice, aux->adjacentes->vertice, aux->adjacentes->peso, aux->meios->codigo);
//                 aux = aux->seguinte;
//             }
//         }
//         fclose(fp);
//         fclose(fpb);
//         printf("Guardado no ficheiro com sucesso!\n");
//     }
//     else
//     {
//         if (fp == NULL)
//         {
//             printf("O ficheiro contas.txt não existe!\n");
//         }
//         else if (fpb == NULL)
//         {
//             printf("O ficheiro contas.bin não existe!\n");
//         }
//         else
//         {
//             printf("Houve um erro na pesquisa dos ficheiros!\n");
//         }
//     }
// }

// Criar um novo grafo
Grafo *criarGrafo()
{
    Grafo *grafo = malloc(sizeof(Grafo));
    if (grafo != NULL)
    {
        *grafo = malloc(sizeof(struct grafos));
        if (*grafo != NULL)
        {
            strcpy((*grafo)->vertice, "///thesaurus.sharers.blizzards");
            (*grafo)->meios = NULL;
            (*grafo)->seguinte = NULL;

            criarVertice(grafo, "///dimly.nuttier.pitch");
            criarVertice(grafo, "///babbled.trifling.consoled");
            criarAresta(*grafo, "///thesaurus.sharers.blizzards", "///babbled.trifling.consoled", 100);
            criarAresta(*grafo, "///thesaurus.sharers.blizzards", "///dimly.nuttier.pitch", 150);

            printf("Grafo criado com sucesso!\n");
            return grafo;
        }
        else
        {
            free(grafo);
            grafo = NULL;
        }
    }
    return NULL;
}

// Criar um novo vértice
int criarVertice(Grafo *grafo, char novoVertice[])
{
    Grafo novo = malloc(sizeof(struct grafos));
    if (novo != NULL)
    {
        strcpy(novo->vertice, novoVertice);
        novo->meios = NULL;
        novo->seguinte = *grafo;
        *grafo = novo;
        return (1);
    }
    else
        return (0);
}

// Verificar se um vértice existe
int existeVertice(Grafo grafo, char vertice[])
{
    while (grafo != NULL)
    {
        if (strcmp(grafo->vertice, vertice) == 0)
            return (1);
        else
            grafo = grafo->seguinte;
    }
    return (0);
}

// Criar uma nova aresta
int criarAresta(Grafo grafo, char origem[], char destino[], float peso)
{
    Adjacente novo;
    if (existeVertice(grafo, origem) && existeVertice(grafo, destino))
    {
        while (strcmp(grafo->vertice, origem) != 0)
            grafo = grafo->seguinte;
        novo = malloc(sizeof(struct grafos));
        if (novo != NULL)
        {
            strcpy(novo->vertice, destino);
            novo->peso = peso;
            novo->seguinte = grafo->adjacentes;
            grafo->adjacentes = novo;
            return (1);
        }
        else
            return (0);
    }
    else
        return (0);
}

// Listar os vértices adjacentes
void listarAdjacentes(Grafo *grafo, char vertice[])
{
    Adjacente aux;
    if (existeVertice(*grafo, vertice))
    {
        Grafo grafoAux = *grafo;
        while (strcmp(grafoAux->vertice, vertice) != 0)
        {
            grafoAux = grafoAux->seguinte;
            if (grafoAux == NULL)
            {
                printf("Vertice não encontrado.\n");
                return;
            }
        }
        aux = grafoAux->adjacentes;
        while (aux != NULL)
        {
            printf("Adjacente:%s Peso:%.2f\n", aux->vertice, aux->peso);
            aux = aux->seguinte;
        }
    }
    else
    {
        printf("Grafo ou vertice não existente.\n");
    }
}

// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeiosGrafo(Grafo *grafo, char geocodigo[])
{
    Grafo grafoAux = *grafo;
    while ((grafoAux != NULL) && (strcmp(grafoAux->vertice, geocodigo) != 0))
        grafoAux = grafoAux->seguinte;
    if (grafoAux != NULL)
    {
        Meio aux = grafoAux->meios;
        if (aux == NULL)
            printf("sem meios de transporte\n");
        else
            while (aux != NULL)
            {
                printf("Meio: %d\n", aux->codigo);
                aux = aux->seguinte;
            }
    }
    else
        printf("geocodigo inexistente\n");
}
