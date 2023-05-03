#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contas/auth/auth.h"
#include "menus/menus.h"
#include "contas/conta/conta.h"
#include "manager/fileManager.h"
#include "meios/meio.h"

int main()
{
	Conta *contas = NULL; // Lista ligada vazia
	Meio *meios = NULL;	// Lista ligada vazia
	contas = lerContas();
	meios = lerMeios();
	menuPrincipal(contas, meios);
	printf("A guardar contas...\n");
	guardarContas(contas);
	printf("A guardar meios...\n");
	guardarMeios(meios);

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
	printf("Memória libertada com sucesso!\n");

	return (0);
}
