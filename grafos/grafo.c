#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo.h"
#include "../meios/meio.h"
#include "../manager/fileManager.h"

// Ler grafo do ficheiro
Grafo *lerGrafo(Meio *meios)
{
    FILE *fp;
    char linha[100], vertice[100];

    Grafo *grafo = NULL;

    fp = fopen("./storage/grafo.txt", "r");
    if (fp != NULL)
    {
        while (fgets(linha, sizeof(linha), fp) != NULL)
        {
            // Remover o \n do fim da linha
            linha[strcspn(linha, "\n")] = '\0';

            printf("%s\n", linha);

            if (linha[0] == '/')
            {
                // Linha é um vertice
                strcpy(vertice,linha);
                criarVertice(&grafo, linha);
            }
        }

        // Reset do pointer para o inicio do ficheiro
        fseek(fp, 0, SEEK_SET);
        
        while (fgets(linha, sizeof(linha), fp) != NULL)
        {
            // Remover o \n do fim da linha
            linha[strcspn(linha, "\n")] = '\0';

            printf("%s\n", linha);

            if (linha[0] == '/')
            {
                // Linha é um vertice
                strcpy(vertice,linha);
            } 
            else if (linha[0] == '_')
            {
                // Linha é uma aresta
                char adjacente[100];
                float peso;
                sscanf(linha, "_%[^;];%f", adjacente, &peso);
                criarAresta(&grafo, vertice, adjacente, peso);
            }
            else if (linha[0] == '-')
            {
                // Linha que tem separador "-----"
                // Passar para a próxima linha
            }
            else
            {
                // Linha é um meio de transporte
                int id_meio;
                char tipo[50];
                float bateria, autonomia;
                sscanf(linha, "%d;%[^;];%f;%f", &id_meio, tipo, &bateria, &autonomia);
                adicionarMeio(&grafo, meios, vertice, id_meio);
            }
        }

        fclose(fp);
        printf("Grafo carregado do ficheiro com sucesso!\n");
        return grafo;
    }

    printf("O ficheiro grafo.txt não pode ser aberto!\n");
    return NULL;
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
        while (aux != NULL)
        {
            //printf("%s\n", aux->vertice);
            fprintf(fp, "%s\n", aux->vertice);
            fprintf(fpb, "%s\n", aux->vertice);

            Adjacente *adj = aux->adjacentes;
            while (adj != NULL)
            {
                //printf("_%s;%.2f\n", adj->vertice, adj->peso);
                fprintf(fp, "_%s;%.2f\n", adj->vertice, adj->peso);
                fprintf(fpb, "_%s;%.2f\n", adj->vertice, adj->peso);
                adj = adj->seguinte;
            }

            Meio *meio = aux->meios;
            while (meio != NULL)
            {
                //printf("%d;%s;%.2f;%.2f\n", meio->codigo, meio->tipo, meio->bateria, meio->autonomia);
                fprintf(fp, "%d;%s;%.2f;%.2f\n", meio->codigo, meio->tipo, meio->bateria, meio->autonomia);
                fprintf(fpb, "%d;%s;%.2f;%.2f\n", meio->codigo, meio->tipo, meio->bateria, meio->autonomia);
                meio = meio->seguinte;
            }

            aux = aux->seguinte;
            fprintf(fp, "-----\n");
            fprintf(fpb, "-----\n");
        }
        fclose(fp);
        fclose(fpb);
        printf("Grafo guardado no ficheiro com sucesso!\n");
    }
    else
    {
        if (fp == NULL)
        {
            printf("O ficheiro grafo.txt não pode ser aberto!\n");
        }
        else if (fpb == NULL)
        {
            printf("O ficheiro grafo.bin não pode ser aberto!\n");
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
        grafo->meios = NULL;
        grafo->seguinte = NULL;

        criarVertice(&grafo, "///porto.porto.porto");
        criarVertice(&grafo, "///lisboa.lisboa.lisboa");
        criarAresta(&grafo, "///braga.braga.braga", "///porto.porto.porto", 100);
        criarAresta(&grafo, "///braga.braga.braga", "///lisboa.lisboa.lisboa", 150);
        criarAresta(&grafo, "///porto.porto.porto", "///lisboa.lisboa.lisboa", 200);
        criarAresta(&grafo, "///porto.porto.porto", "///braga.braga.braga", 100);
        criarAresta(&grafo, "///lisboa.lisboa.lisboa", "///braga.braga.braga", 150);
        criarAresta(&grafo, "///lisboa.lisboa.lisboa", "///porto.porto.porto", 200);
        adicionarMeio(&grafo, meios, "///braga.braga.braga", 1);
        adicionarMeio(&grafo, meios, "///porto.porto.porto", 2);
        adicionarMeio(&grafo, meios, "///porto.porto.porto", 3);
        adicionarMeio(&grafo, meios, "///lisboa.lisboa.lisboa", 4);

        printf("\nGrafo criado com sucesso!\n");
    }
    else
    {
        printf("\nNão foi possível alocar memória para o Grafo!\n");
    }

    return grafo;
}

// Criar um novo vértice
void criarVertice(Grafo **grafo, char novoVertice[])
{
    Grafo *novo = malloc(sizeof(struct grafos));
    if (novo != NULL)
    {
        strcpy(novo->vertice, novoVertice);
        novo->meios = NULL;
        novo->seguinte = *grafo; // Set the next pointer to the current head
        *grafo = novo;           // Update the head pointer to the new node

        printf("\nVértice criado com sucesso!\n");
    }
    else
    {
        printf("\nNão foi possível alocar memória para criação do vértice!\n");
    }
}

// Listar os vértices
void listarVertices(Grafo *grafo)
{
    if (grafo != NULL)
    {
        printf("\n----  LISTA DE VÉRTICES  ----\n");
        printf("-----------------------------\n");

        Grafo *aux = grafo;

        while (aux != NULL)
        {
            printf("| %-25s |\n", aux->vertice);
            printf("-----------------------------\n");
            aux = aux->seguinte;
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
        Grafo *grafoAtual = *grafo;
        while (strcmp(grafoAtual->vertice, origem) != 0)
        {
            grafoAtual = grafoAtual->seguinte;
        }

        Adjacente *novo = malloc(sizeof(struct adjacentes));
        if (novo != NULL)
        {
            strcpy(novo->vertice, destino);
            novo->peso = peso;
            novo->seguinte = grafoAtual->adjacentes;
            grafoAtual->adjacentes = novo;
            printf("\nAresta com origem %s \ne destino %s criada com sucesso!\n", origem, destino);
        }
        else
        {
            printf("\nNão foi possível alocar memória para criação da aresta!\n");
        }
    }
    else
    {
        printf("\nNão foi possível criar a aresta!\n");
    }
}

// Listar os vértices adjacentes
void listarAdjacentes(Grafo *grafo, char vertice[])
{
    if (existeVertice(grafo, vertice))
    {
        while (strcmp(grafo->vertice, vertice) != 0)
        {
            grafo = grafo->seguinte;
            if (grafo == NULL)
            {
                printf("\nVertice não encontrado!\n");
                return;
            }
        }

        Adjacente *adj = grafo->adjacentes;

        if (adj != NULL)
        {
            printf("\n---  Adjacentes a %-s  ---\n", vertice);
            printf("----------------------------------------\n");
            printf("|          Adjacente          |  Peso  |\n");
            printf("----------------------------------------\n");

            while (adj != NULL)
            {
                printf("| %-27s | %6.2f |\n", adj->vertice, adj->peso);
                printf("----------------------------------------\n");
                adj = adj->seguinte;
            }
        }
        else
        {
            printf("\nO vértice %s não possui adjacentes.\n", vertice);
        }
    }
    else
    {
        printf("\nO Grafo ou o vértice não existe!\n");
    }
}

// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeiosGrafo(Grafo *grafo, Meio *meios, char geocodigo[])
{
    while ((grafo != NULL) && (strcmp(grafo->vertice, geocodigo) != 0))
    {
        grafo = grafo->seguinte;
    }
    if (grafo != NULL)
    {
        printf("\n----  GEOCÓDIGO: %s  ----\n", geocodigo);
        printf("--------------------------------------------------\n");
        printf("|  Código  |  Tipo        |  Bateria | Autonomia |\n");
        printf("--------------------------------------------------\n");

        Meio *aux = grafo->meios;

        if (aux == NULL)
        {
            printf("|        Não existem meios de transporte!        |\n");
            printf("--------------------------------------------------\n");
        }
        else
        {
            while (aux != NULL)
            {
                // Find the corresponding meio in the meios list
                Meio *meio = existeMeio(meios, aux->codigo);
                if (meio != NULL)
                {
                    printf("| %8d | %-12s |  %6.2f%% |  %6.2fKm |\n", aux->codigo, meio->tipo, meio->bateria, meio->autonomia);
                    printf("--------------------------------------------------\n");
                }
                aux = aux->seguinte;
            }
        }
    }
    else
    {
        printf("\nO geocódigo %s não existe!\n", geocodigo);
    }
}

// Adicionar um meio de transporte a uma determinada localização
void adicionarMeio(Grafo **grafo, Meio *meios, char geocodigo[], int codigo)
{
    if (existeVertice(*grafo, geocodigo))
    {
        Grafo *grafoAtual = *grafo;
        while (strcmp(grafoAtual->vertice, geocodigo) != 0)
        {
            grafoAtual = grafoAtual->seguinte;
        }
        Meio *meioAtual = meios;
        meioAtual = existeMeio(meioAtual, codigo);

        if (meioAtual != NULL)
        {
            // Adicionar o meio de transporte ao vértice
            Meio *novo = malloc(sizeof(struct meios));
            if (novo != NULL)
            {
                novo->codigo = meioAtual->codigo;
                strcpy(novo->tipo, meioAtual->tipo);
                novo->autonomia = meioAtual->autonomia;
                novo->bateria = meioAtual->bateria;
                novo->custo = meioAtual->custo;
                novo->id_cliente = meioAtual->id_cliente;
                novo->inicio_aluguer = meioAtual->inicio_aluguer;
                novo->seguinte = grafoAtual->meios;
                grafoAtual->meios = novo;
                printf("\nMeio de transporte %d adicionado com sucesso a %s!\n", codigo, geocodigo);
            }
            else
            {
                printf("\nNão foi possível alocar memória para o meio de transporte!\n");
            }
        }
        else
        {
            printf("\nO meio de transporte %d não existe!\n", codigo);
        }
    }
    else
    {
        printf("\nNão foi possível adicionar o meio de transporte!\n");
    }
}