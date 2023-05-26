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
Grafo *criarGrafo(Meio *meios)
{
    Grafo *grafo = malloc(sizeof(Grafo));
    if (grafo != NULL)
    {
        strcpy(grafo->vertice, "///thesaurus.sharers.blizzards");
        grafo->meios = meios;
        grafo->seguinte = NULL;

        criarVertice(&grafo, "///babbled.trifling.consoled");
        criarVertice(&grafo, "///dimly.nuttier.pitch");
        criarAresta(&grafo, "///thesaurus.sharers.blizzards", "///babbled.trifling.consoled", 100);
        criarAresta(&grafo, "///thesaurus.sharers.blizzards", "///dimly.nuttier.pitch", 150);

        printf("\nGrafo criado com sucesso!\n");
        return grafo;
    }
    else
    {
        free(grafo);
        grafo = NULL;
        printf("\nNão foi possível criar o Grafo!\n");
        return grafo;
    }
}

// Criar um novo vértice
void criarVertice(Grafo **grafo, char novoVertice[])
{
    Grafo *novo = malloc(sizeof(struct grafos));
    if (novo != NULL)
    {
        strcpy(novo->vertice, novoVertice);
        novo->meios = NULL;
        novo->seguinte = NULL;

        if (*grafo == NULL)
        {
            *grafo = novo;
        }
        else
        {
            Grafo *temp = *grafo;
            while (temp->seguinte != NULL)
            {
                temp = temp->seguinte;
            }
            temp->seguinte = novo;
        }
        printf("\nVértice criado com sucesso!\n");
        return;
    }
    printf("\nNão foi possível alocar memória para criação do vértice!\n");
}


// Listar os vértices
void listarVertices(Grafo *grafo)
{
    if (grafo != NULL)
    {
        while (grafo != NULL)
        {
            printf("%s\n", grafo->vertice);
            grafo = grafo->seguinte;
        }
    }
    else
    {
        printf("\nO grafo encontra-se vazio!\n");
    }
}

// Verificar se um vértice existe
int existeVertice(Grafo *grafo, char vertice[])
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
void criarAresta(Grafo **grafo, char origem[], char destino[], float peso)
{
    if (existeVertice(*grafo, origem) && existeVertice(*grafo, destino))
    {
        while (strcmp((*grafo)->vertice, origem) != 0)
        {
            *grafo = (*grafo)->seguinte;
        }
        Adjacente *novo = malloc(sizeof(struct adjacentes));
        if (novo != NULL)
        {
            strcpy(novo->vertice, destino);
            novo->peso = peso;
            novo->seguinte = (*grafo)->adjacentes;
            (*grafo)->adjacentes = novo;
            printf("\nAresta com origem %s \ne destino %s criada com sucesso!\n", origem, destino);
            return;
        }
    }
    printf("\nNão foi possível criar a aresta!\n");
}

// Listar os vértices adjacentes
void listarAdjacentes(Grafo *grafo, char vertice[])
{
    Adjacente *adj;
    if (existeVertice(grafo, vertice))
    {
        while (strcmp(grafo->vertice, vertice) != 0)
        {
            *grafo = *grafo->seguinte;
            if (grafo == NULL)
            {
                printf("Vertice não encontrado.\n");
                return;
            }
        }
        adj = grafo->adjacentes;
        while (adj != NULL)
        {
            printf("Adjacente:%s Peso:%.2f\n", adj->vertice, adj->peso);
            adj = adj->seguinte;
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
    while ((grafo != NULL) && (strcmp(grafo->vertice, geocodigo) != 0))
    {
        grafo = grafo->seguinte;
    }
    if (grafo != NULL)
    {
        Meio *aux = grafo->meios;
        if (aux == NULL)
            printf("\nNão existem meios de transporte!\n");
        else
            while (aux != NULL)
            {
                printf("Meio: %d\n", aux->codigo);
                aux = aux->seguinte;
            }
    }
    else
        printf("\nO geocódigo %s não existe!\n", geocodigo);
}
