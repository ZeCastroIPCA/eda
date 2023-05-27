#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contas/auth/auth.h"
#include "menus/menus.h"
#include "contas/conta/conta.h"
#include "manager/fileManager.h"
#include "meios/meio.h"
#include "grafos/grafo.h"

int main()
{
	// Pointer de contas, meios e grafo
	Conta *contas = NULL;
	Meio *meios = NULL;
	Grafo *grafo = NULL;

	// Ler contas, meios e grafo
	contas = lerContas();
	meios = lerMeios();
	grafo = lerGrafo(meios);

	// Pointer de grafo
	//grafo = criarGrafo(meios);
	
	// Verifificar se o grafo foi criado com sucesso
	// printf("----------------------------------------------------------------\n");
	// listarVertices(grafo);
    // listarAdjacentesMan(grafo, "///braga.braga.braga");
    // listarMeiosGrafoMan(grafo, meios, "///porto.porto.porto");
	// printf("----------------------------------------------------------------\n");

	// Menu principal
	menuPrincipal(contas, meios, grafo);

	// Guardar contas e meios
	printf("A guardar contas...\n");
	guardarContas(contas);
	printf("A guardar meios...\n");
	guardarMeios(meios);
	printf("A guardar grafo...\n");
	guardarGrafo(grafo);

	// libertar a memória alocada
	Conta *conta_aux = contas;
	while (conta_aux != NULL)
	{
		Conta *conta_aux2 = conta_aux;
		conta_aux = conta_aux->seguinte;
		free(conta_aux2);
	}
	Meio *meio_aux = meios;
	while (meio_aux != NULL)
	{
		Meio *meio_aux2 = meio_aux;
		meio_aux = meio_aux->seguinte;
		free(meio_aux2);
	}
	Grafo *grafo_aux = grafo;
	while (grafo_aux != NULL)
	{
		Grafo *grafo_aux2 = grafo_aux;
		grafo_aux = grafo_aux->seguinte;
		free(grafo_aux2);
	}
	printf("Memória libertada com sucesso!\n");

	return (0);
}
