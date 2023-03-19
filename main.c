#include <stdio.h>
#include "meios/meio.h"
#include "contas/registo.h"
#include "menus/menus.h"
#include "login/handleLogin.h"

int main()
{
	Conta *contas = NULL; // Lista ligada vazia
	contas = lerConta();
	contas = menuPrincipal(contas);
	guardarContas(contas);
	return (0);
}
