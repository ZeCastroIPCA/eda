#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo.h"
#include "../meios/meio.h"
#include "../manager/fileManager.h"

// Ler grafo do ficheiro
Grafo *lerGrafo()
{
    FILE *fp;
    char vertice[50], adjacente[50];
    float peso;
    int id_meio;
    Grafo *aux = NULL;
    fp = fopen("./storage/grafo.txt", "r");
    if (fp != NULL)
    {
        Grafo *novo = malloc(sizeof(fp));
        if (novo != NULL)
        {
            printf("\nVértices disponíveis:\n");
            while (!feof(fp))
            {
                printf("%s %s %.2f %d\n", aux->vertice, aux->adjacentes->vertice, aux->adjacentes->peso, aux->meios->codigo);
                fscanf(fp, "%[^;];%[^;];%f;%d\n", vertice, adjacente, &peso, &id_meio);
                aux = inserirGrafoFile(aux, vertice, adjacente, peso, id_meio);
                novo = aux;
            }
            fclose(fp);
            return (aux);
        }
    }
    printf("\nFicheiro do grafo vazio!\n");
    return (NULL);
}

// Guarda o grafo em ficheiros de texto e binário
void guardarGrafo(Grafo *grafo)
{
    FILE *fp, *fpb;
    fp = fopen("./storage/grafo.txt", "w+");
    fpb = fopen("./storage/grafo.bin", "wb+");
    if (fp != NULL && fpb != NULL)
    {
        Grafo *aux = grafo;
        if (aux != NULL)
        {
            while (aux != NULL)
            {
                Adjacente *aux_adj = aux->adjacentes;
                while (aux_adj != NULL)
                {
                    Meio *aux_meio = aux->meios;
                    while (aux_meio != NULL)
                    {
                        printf("%s;%s;%f;%d\n", aux->vertice, aux_adj->vertice, aux_adj->peso, aux_meio->codigo);
                        fprintf(fp, "%s;%s;%f;%d\n", aux->vertice, aux_adj->vertice, aux_adj->peso, aux_meio->codigo);
                        fprintf(fpb, "%s;%s;%f;%d\n", aux->vertice, aux_adj->vertice, aux_adj->peso, aux_meio->codigo);
                        aux_meio = aux_meio->seguinte;
                    }
                    aux_adj = aux_adj->seguinte;
                }
                aux = aux->seguinte;
            }
        }
        fclose(fp);
        fclose(fpb);
        printf("Guardado no ficheiro com sucesso!\n");
    }
    else
    {
        if (fp == NULL)
        {
            printf("O ficheiro contas.txt não existe!\n");
        }
        else if (fpb == NULL)
        {
            printf("O ficheiro contas.bin não existe!\n");
        }
        else
        {
            printf("Houve um erro na pesquisa dos ficheiros!\n");
        }
    }
}

// Criar um novo grafo
Grafo *criarGrafo(Meio *meios)
{
    Grafo *grafo = malloc(sizeof(Grafo));
    if (grafo != NULL)
    {
        strcpy(grafo->vertice, "///braga.braga.braga");
        grafo->meios = meios;
        grafo->seguinte = NULL;

        criarVertice(&grafo, "///porto.porto.porto");
        criarVertice(&grafo, "///lisboa.lisboa.lisboa");
        criarAresta(&grafo, "///braga.braga.braga", "///porto.porto.porto", 100);
        criarAresta(&grafo, "///braga.braga.braga", "///lisboa.lisboa.lisboa", 150);

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
                printf("\nVertice não encontrado!\n");
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
        printf("\nO Grafo ou o vertice não existe!\n");
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
