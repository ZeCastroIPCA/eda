#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../contas/conta/conta.h"
#include "../contas/auth/auth.h"
#include "../meios/meio.h"
#include "menus.h"

void menuCliente(Conta *contas, Conta *conta, Meio *meios)
{
	int op, conta_op, aluguer_op, meio_cod;
	float saldoCarregar;
	while (op != 0)
	{
		printf("-------------------------\n");
		printf("|     Bem vindo %-7s |\n|     Saldo: %05.2f      |\n", conta->nome, conta->saldo);
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
			if(conta->meio_id != 0){
				printf("Pretente terminar o aluguer atual?\n(1 - Sim | 0 - Não):");
				scanf("%d", &aluguer_op);
				if (aluguer_op)
				{
					conta->meio_id = 0;
				}
				break;
			}
			printf("Qual o meio que pretende alugar?\nSerão debitados da sua conta 0,5€\nID do meio:");
			scanf("%d", &meio_cod);
			if (existeMeio(meios, meio_cod))
			{
				conta->meio_id = meio_cod;
				conta->saldo -= 0.5;
				printf("\nMeio alugado com sucesso!\n");
				break;
			}
			printf("\nO meio que pretende alugar não existe!\n");
			break;
		case 2:
			printf("Carregar saldo:");
			scanf("%f", &saldoCarregar);
			conta->saldo += saldoCarregar;
			printf("\nSaldo carregado com sucesso!\n");
			break;
		case 3:
			printf("\nTem a certeza que pretende apagar a sua conta?\nId: %d\n(1 - Sim | 0 - Não):", conta->codigo);
			scanf("%d", &conta_op);
			if (conta_op)
			{
				removerConta(contas, conta->codigo);
				printf("\nA sua conta foi apagada com sucesso!\n");
				op = 0;
				break;
			}
			printf("\nA sua conta não foi apagada!\n\n");
			break;
		default:
			op != 0 && printf("\nOpção inválida!\n");
			break;
		}
	};
}

void menuGestorGestores(Conta *contas)
{
	int op;
	printf("\n------------------------------\n");
	printf("|     Gestão de Gestores     |\n");
	printf("------------------------------\n");
	printf("1 - Criar nova conta de gestor\n");
	printf("2 - Listar todos os gestores\n");
	printf("3 - Alterar dados de um gestor\n");
	printf("4 - Eliminar um gestor\n");
	printf("0 - Voltar\n");
	printf("Opcao:");
	scanf("%d", &op);
}

void menuGestorMeios(Meio *meios)
{
	int op;
	printf("\n------------------------------\n");
	printf("|       Gestão de Meios      |\n");
	printf("------------------------------\n");
	printf("1 - Registar um meio elétrico\n");
	printf("2 - Listar todos os meios elétricos\n");
	printf("3 - Alterar dados de um meio elétrico\n");
	printf("4 - Eliminar um meio elétrico\n");
	printf("0 - Voltar\n");
	printf("Opcao:");
	scanf("%d", &op);
}

void menuGestorClientes(Conta *contas)
{
	int op;
	int id;
	do
	{
		printf("\n------------------------------\n");
		printf("|     Gestão de Clientes     |\n");
		printf("------------------------------\n");
		printf("1 - Registar um novo cliente\n");
		printf("2 - Listar todos os clientes\n");
		printf("3 - Alterar dados de um cliente\n");
		printf("4 - Eliminar um cliente\n");
		printf("0 - Voltar\n");
		printf("Opcao:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			handleRegisto(contas);
			break;
		case 2:
			listarContas(contas);
			break;
		case 3:
			printf("\nID a alterar:");
			scanf("%d", &id);
			alterarConta(contas, id);
			break;
		case 4:
			printf("\nID a eliminar:");
			scanf("%d", &id);
			removerConta(contas, id);
			break;
		default:
			op != 0 && printf("\nOpção inválida!\n");
			break;
		}
	} while (op != 0);
}

void menuGestorPrincipal(Conta *contas, Meio *meios)
{
	int op;
	do
	{
		printf("\n------------------------------\n");
		printf("|       Menu de Gestão       |\n");
		printf("------------------------------\n");
		printf("1 - Gestão de Meios Elétricos\n");
		printf("2 - Gestão de Clientes\n");
		printf("3 - Gestão de Gestores\n");
		printf("0 - Voltar\n");
		printf("Opcao:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			menuGestorMeios(meios);
			break;
		case 2:
			menuGestorClientes(contas);
			break;
		case 3:
			menuGestorGestores(contas);
			break;
		default:
			op != 0 && printf("\nOpção inválida!\n");
			break;
		}
	} while (op != 0);
}

Conta *menuPrincipal(Conta *contas, Meio *meios)
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
			handleLogin(contas, meios);
			break;
		case 2:
			contas = handleRegisto(contas);
			break;
		default:
			op != 0 && printf("\nOpção inválida!\n");
			break;
		}
	} while (op != 0);
	return (contas);
}