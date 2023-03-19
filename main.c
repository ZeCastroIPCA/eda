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
	Meio *meios = NULL;		   // Lista ligada vazia
	contas = lerContas();
	meios = lerMeios();
	contas = menuPrincipal(contas, meios);
	guardarContas(contas);
	return (0);
}
