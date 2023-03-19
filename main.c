#include <stdio.h>
#include "contas/auth/auth.h"
#include "menus/menus.h"
#include "contas/conta/conta.h"
#include "manager/fileManager.h"

int main()
{
	Conta *contas = NULL; // Lista ligada vazia
	contas = lerContas();
	menuPrincipal(contas);
	guardarContas(contas);
	return (0);
}
