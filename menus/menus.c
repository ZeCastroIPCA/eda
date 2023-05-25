#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "menus.h"
#include "../contas/conta/conta.h"
#include "../contas/auth/auth.h"
#include "../meios/meio.h"

void menuCliente(Conta *contas, Conta *conta, Meio *meios)
{
	int op;

	while (op != 0)
	{
		printf("-------------------------\n");
		printf("|     Bem vindo %-7s |\n|     Saldo: %6.2f     |\n", conta->nome, conta->saldo);
		printf("-------------------------\n");
		conta->meio_id ? printf("1 - Terminar aluguer atual\n") : printf("1 - Alugar um meio elétrico\n");
		printf("2 - Carregar saldo\n");
		printf("3 - Apagar conta\n");
		printf("0 - Voltar\n");
		printf("Opcao:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			alugarMeio(contas, conta, meios);
			break;
		case 2:
			carregarSaldo(conta);
			break;
		case 3:
			// O parametro 1 indica que é o cliente que está a apagar a conta
			removerConta(contas, conta->codigo, 1);
			// A definição de op a 0 faz com que o programa volte ao menu anterior
			op = 0;
			break;
		default:
			op != 0 && printf("\nOpção inválida!\n");
			break;
		}
	};
}

void menuGestorMeios(Meio *meios, Grafo *grafo)
{
	int op;
	do
	{
		printf("\n------------------------------\n");
		printf("|       Gestão de Meios      |\n");
		printf("------------------------------\n");
		printf("1 - Registar um meio elétrico\n");
		printf("2 - Listar todos os meios elétricos\n");
		printf("3 - Listar meios num Geo Código\n");
		printf("4 - Alterar dados de um meio elétrico\n");
		printf("5 - Eliminar um meio elétrico\n");
		printf("0 - Voltar\n");
		printf("Opcao:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			inserirMeio(meios, grafo);
			break;
		case 2:
			listarMeios(meios);
			break;
		case 3:
			listarMeiosPorGeoCode(grafo);
			break;
		case 4:
			alterarMeio(meios, grafo);
			break;
		case 5:
			removerMeio(meios);
			break;
		default:
			op != 0 && printf("\nOpção inválida!\n");
			break;
		}
	} while (op != 0);
}

void menuGestorContas(Conta *contas)
{
	int op;
	do
	{
		printf("\n------------------------------\n");
		printf("|     Gestão de Contas       |\n");
		printf("------------------------------\n");
		printf("1 - Registar uma nova conta\n");
		printf("2 - Listar todos os clientes\n");
		printf("3 - Listar todos os gestores\n");
		printf("4 - Alterar dados de uma conta\n");
		printf("5 - Eliminar uma conta\n");
		printf("0 - Voltar\n");
		printf("Opcao:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			// O parametro 1 indica que é um registo de um gestor
			handleRegisto(contas, 1);
			break;
		case 2:
			listarContas(contas, "cliente");
			break;
		case 3:
			listarContas(contas, "gestor");
			break;
		case 4:
			alterarConta(contas);
			break;
		case 5:
			// O valor do segundo parametro a 0 é meramente ilustrativo, pois o valor é pedido ao utilizador dentro da função
			// O valor do terceiro parametro a 0 indica que é um gestor que está a apagar a conta
			removerConta(contas, 0, 0);
			break;
		default:
			op != 0 && printf("\nOpção inválida!\n");
			break;
		}
	} while (op != 0);
}

void menuGestorPrincipal(Conta *contas, Meio *meios, Grafo *grafo)
{
	int op;
	do
	{
		printf("\n------------------------------\n");
		printf("|       Menu de Gestão       |\n");
		printf("------------------------------\n");
		printf("1 - Gestão de Meios Elétricos\n");
		printf("2 - Gestão de Contas\n");
		printf("0 - Voltar\n");
		printf("Opcao:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			menuGestorMeios(meios, grafo);
			break;
		case 2:
			menuGestorContas(contas);
			break;
		default:
			op != 0 && printf("\nOpção inválida!\n");
			break;
		}
	} while (op != 0);
}

void menuPrincipal(Conta *contas, Meio *meios, Grafo *grafo)
{
	int op;
	do
	{
		printf("\n-----------------------------------------------------\n");
		printf("|       Programa de gestão de meios elétricos       |\n");
		printf("-----------------------------------------------------\n");
		printf("1 - Login\n");
		printf("2 - Registar\n");
		printf("0 - Sair\n");
		printf("Opcao:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			handleLogin(contas, meios, grafo);
			break;
		case 2:
			// O parametro 0 indica que é um registo de cliente
			handleRegisto(contas, 0);
			break;
		default:
			op != 0 && printf("\nOpção inválida!\n");
			break;
		}
	} while (op != 0);
}