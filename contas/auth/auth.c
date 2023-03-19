#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "../../menus/menus.h"
#include "../conta/conta.h"
#include "../../meios/meio.h"

// Verificar se o email e a password estão corretos e se o utilizador é um cliente ou gestor
void handleLogin(Conta *contas, Meio *meios)
{
    Conta *conta = NULL;
    char email[50], password[50];
    do
    {   
        getchar();
        printf("Email:");
        scanf("%[^\n]s", email);
        getchar();
        printf("Password:");
        scanf("%[^\n]s", password);
        conta = login(contas, email, password);
        if (conta == 0)
        {
            printf("\nO login falhou!\nTente outra vez.\n");
        }
    } while (conta == 0);
    printf("\nLogin efetuado com sucesso!\n");

    if (strcmp(conta->tipo, "cliente") == 0)
    {
        menuCliente(contas, conta, meios);
    }
    else if (strcmp(conta->tipo, "gestor") == 0)
    {
        menuGestorPrincipal(contas, meios);
    }
}

// Criar uma nova conta cliente
Conta *handleRegisto(Conta* contas)
{
    char email[50], password[50], nome[50], morada[50], nif[9];
    printf("Email: ");
    scanf("%s", email);
    printf("Password: ");
    scanf("%s", password);
    getchar();
    printf("Nome: ");
    scanf("%[^\n]s", nome);
    getchar();
    printf("Morada: ");
    scanf("%[^\n]s", morada);
    printf("NIF: ");
    scanf("%s", nif);
    return registo(contas, email, password, nome, morada, nif);
}

// Verificar se o email e a password estão corretos
Conta *login(Conta *inicio, char email[], char pass[])
{
    while (inicio != NULL)
    {
        if (strcmp(inicio->email, email) == 0 && strcmp(inicio->password, pass) == 0)
            return (inicio);
        inicio = inicio->seguinte;
    }
    return (0);
}

// Criar uma nova conta
Conta *registo(Conta *inicio, char email[], char pass[], char nome[], char morada[], char nif[])
{
  int cod = inicio->codigo;
  while (1)
  {
    if (!existeConta(inicio, cod))
    {
      Conta *novo = malloc(sizeof(struct contas));
      if (novo != NULL)
      {
        novo->codigo = cod;
        strcpy(novo->tipo, "cliente");
        strcpy(novo->email, email);
        strcpy(novo->password, pass);
        strcpy(novo->nome, nome);
        strcpy(novo->morada, morada);
        strcpy(novo->nif, nif);
        novo->saldo = 0;
        novo->meio_id = 0;
        novo->seguinte = inicio;
        printf("Conta criada com sucesso!\n");
        return (novo);
      }
      else
      {
        printf("Não foi possível alocar memória\npara criação de um novo utilizador!\n");
        return (inicio);
      }
      break;
    }
    else
      cod++;
  }
}





