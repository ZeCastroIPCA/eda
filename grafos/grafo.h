#pragma once
#include <stdio.h>

#define STRING_SIZE 100

typedef struct meios Meio;

typedef struct adjacentes
{
	char vertice[STRING_SIZE]; // geocódigo what3words
	float peso;
	struct adjacentes *seguinte;
} Adjacente;

typedef struct grafos
{
	char vertice[STRING_SIZE]; // geocódigo what3words
	Adjacente *adjacentes;
	Meio *meios; // Lista ligada dos meios de transporte existentes neste geocódigo
	struct grafos *seguinte;
} Grafo;

Grafo *criarGrafo(Meio *meios); // Cria um novo grafo
void criarVertice(Grafo **grafo); // Criar um novo vértice
void criarVerticeMan(Grafo **grafo, char novoVertice[]); // Criar um novo vértice manual
void listarVertices(Grafo *grafo); // Listar os vértices do grafo
void criarAresta(Grafo **grafo); // Criar uma nova aresta
void criarArestaMan(Grafo **grafo, char origem[], char destino[], float peso); // Criar uma nova aresta manual
void listarAdjacentes(Grafo *grafo); // Listar os vértices adjacentes a um vértice
void listarAdjacentesMan(Grafo *grafo, char vertice[]); // Listar os vértices adjacentes a um vértice
void listarMeiosGrafo(Grafo *grafo, Meio *meios); // Listar os códigos dos meios de transporte presente numa determinada localização introduzida pelo utilizador
void listarMeiosGrafoNaoExistentes(Grafo *grafo, Meio *meios); // Listar os códigos dos meios de transporte presente em todas as localizações
void listarMeiosGrafoMan(Grafo *grafo, Meio *meios, char geocodigo[]); // Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void adicionarMeio(Grafo **grafo, Meio *meios); // Adicionar um meio de transporte a um geocódigo
void adicionarMeioMan(Grafo **grafo, Meio *meios, char geocodigo[], int codigo); // Adicionar um meio de transporte a um geocódigo manualmente
void removerMeioGrafo(Grafo **grafo, int id); // Remover um meio de transporte do seu código

int existeVertice(Grafo *grafo, char vertice[]); // Verificar se um vértice existe

void pesquisaRaio(Grafo* grafo, Meio* meios, char *vertice, float raio, char *tipo, float distancia); // Pesquisa de meios de transporte a um raio de um geocódigo

Grafo *lerGrafo(Meio *meios); // Ler o grafo de um ficheiro
void guardarGrafo(Grafo *grafo); // Guardar o grafo num ficheiro
