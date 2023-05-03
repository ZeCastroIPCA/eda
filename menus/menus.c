#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../contas/conta/conta.h"
#include "../contas/auth/auth.h"
#include "../meios/meio.h"
#include "menus.h"

void menuCliente(Conta *contas, Conta *conta, Meio *meios)
{
	int op, conta_op, aluguer_op, meio_cod;
	float saldoCarregar;

	// meio alugado pelo cliente
	Meio *meio = NULL;

	// encontrar o meio alugado pelo cliente
	Meio *meio_aux = meios;
	while (meio_aux != NULL)
	{
		if (meio_aux->id_cliente == conta->codigo)
		{
			meio = meio_aux;
			break;
		}
		meio_aux = meio_aux->seguinte;
	}

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
			if (conta->meio_id != 0)
			{
				printf("Pretente terminar o aluguer atual?\n(1 - Sim | 0 - Não):");
				scanf("%d", &aluguer_op);
				if (aluguer_op)
				{
					conta->meio_id = 0;
					meio->id_cliente = 0;
					int tempo_alugado = time(NULL) - meio->inicio_aluguer;
					conta->saldo -= tempo_alugado * meio->custo;
					meio->inicio_aluguer = 0;
				}
				break;
			}
			printf("Qual o meio que pretende alugar?\nSerão debitados da sua conta 0,5€\nID do meio:");
			scanf("%d", &meio_cod);
			if (conta->saldo < 0.5)
			{
				printf("\nNão tem saldo suficiente para alugar um meio!\n");
				break;
			}
			else if (existeMeio(meios, meio_cod))
			{
				conta->meio_id = meio_cod;
				meio = existeMeio(meios, meio_cod);
				meio->id_cliente = conta->codigo;
				meio->inicio_aluguer = time(NULL);
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

void menuGestorMeios(Meio *meios)
{
	int op;
	int id;
	do
	{
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
		switch (op)
		{
		case 1:
			inserirMeio(meios);
			break;
		case 2:
			listarMeios(meios);
			break;
		case 3:
			printf("\nID a alterar:");
			scanf("%d", &id);
			alterarMeio(meios, id);
			break;
		case 4:
			printf("\nID a eliminar:");
			scanf("%d", &id);
			if (id)
			{
				removerMeio(meios, id);
				printf("\nO meio %d foi apagado com sucesso!\n", id);
				break;
			}
			printf("\nO meio %d não foi apagado!\n\n", id);
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
	int id;
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
			printf("\nID a alterar:");
			scanf("%d", &id);
			alterarConta(contas, id);
			break;
		case 5:
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
		printf("2 - Gestão de Contas\n");
		printf("0 - Voltar\n");
		printf("Opcao:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			menuGestorMeios(meios);
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

void menuPrincipal(Conta *contas, Meio *meios)
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
			// O parametro 0 indica que é um registo de cliente
			handleRegisto(contas, 0);
			break;
		default:
			op != 0 && printf("\nOpção inválida!\n");
			break;
		}
	} while (op != 0);
}