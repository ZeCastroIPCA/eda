#pragma once
#include <stdio.h>

#define STRING_SIZE 100

typedef struct meios Meio;

// Representação de um grafo orientado e pesado
typedef struct adjacentes
{char vertice[STRING_SIZE]; // geocódigo what3words
 float peso;
 struct adjacentes *seguinte;
} *Adjacente;

typedef struct grafos
{char vertice[STRING_SIZE]; // geocódigo what3words
 Adjacente adjacentes;
 Meio meios; // Lista ligada com os códigos dos meios de transporte existente
	      // neste geocódigo
 struct grafos *seguinte;
} *Grafo;

Grafo *criarGrafo(); // Cria um novo grafo
int criarVertice(Grafo *grafo, char novoVertice[]); // Criar um novo vértice
int criarAresta(Grafo grafo, char origem[], char destino[], float peso); // Criar uma nova aresta
int existeVertice(Grafo grafo, char vertice[]); // Verificar se um vértice existe
void listarAdjacentes(Grafo *grafo, char vertice[]); // Listar os vértices adjacentes a um vértice
void listarMeiosGrafo(Grafo *grafo, char geocodigo[]); // Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro