#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "../../menus/menus.h"
#include "../conta/conta.h"
#include "../../meios/meio.h"
#include "../../grafos/grafo.h"

// Verificar se o email e a password estão corretos e se o utilizador é um cliente ou gestor
void handleLogin(Conta *contas, Meio *meios, Grafo *grafo)
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
    menuCliente(contas, conta, meios, grafo);
  }
  else if (strcmp(conta->tipo, "gestor") == 0)
  {
    menuGestorPrincipal(contas, meios, grafo);
  }
}

// Criar uma nova conta
void handleRegisto(Conta *contas, int who, Grafo *grafo)
{
  char email[50], password[50], nome[50], morada[50], nif[9], tipo[50], localizacao[100];
  int tipoInt = 456; // 456 é um valor aleatório e inválido para o tipo de conta
  if (who == 1)
  {
    do
    {
      if (tipoInt != 456 && tipoInt != 1 && tipoInt != 2)
        printf("\nTipo de conta inválido!\nTente outra vez.\n\n");

      printf("Tipo de conta\n(1 - Cliente | 2 - Gestor):");
      scanf("%d", &tipoInt);
    } while (tipoInt != 456 && tipoInt != 1 && tipoInt != 2);
  }
  strcpy(tipo, tipoInt == 2 ? "gestor" : "cliente");
  printf("Email: ");
  scanf("%s", email);
  printf("Password: ");
  scanf("%s", password);
  getchar();
  if (tipoInt == 456)
  {
    printf("Nome: ");
    scanf("%49s", nome);
    printf("Morada: ");
    scanf("%49s", morada);
    printf("NIF: ");
    scanf("%8s", nif);
    printf("Localização: ");
    scanf("%99s", localizacao);
    // Verificar se existe uma localização com o geocódigo inserido
    while (!existeVertice(grafo, localizacao))
    {
      printf("Não existe nenhuma localização com o geocódigo %s!\n", localizacao);
      printf("Insira um geocódigo válido:");
      scanf("%99s", localizacao);
    }
  }
  else
  {
    strcpy(nome, "n/a");
    strcpy(morada, "n/a");
    strcpy(nif, "n/a");
    strcpy(localizacao, "n/a");
  }

  registo(contas, email, password, nome, morada, nif, tipo, localizacao);
}

// Verificar se o email e a password estão corretos
Conta *login(Conta *contas, char email[], char pass[])
{
  while (contas != NULL)
  {
    if (strcmp(contas->email, email) == 0 && strcmp(contas->password, pass) == 0)
      return (contas);
    contas = contas->seguinte;
  }
  return (0);
}

// Criar uma nova conta
void registo(Conta *contas, char email[], char pass[], char nome[], char morada[], char nif[], char tipo[], char localizacao[])
{
  int cod = contas->codigo;
  const int emailExiste = verificarEmail(contas, email);
  while (1)
  {
    if (!existeConta(contas, cod) && !emailExiste)
    {
      Conta *aux = contas;
      Conta *novo = malloc(sizeof(struct contas));
      if (novo != NULL)
      {
        novo->codigo = cod;
        if (tipo != NULL)
        {
          strcpy(novo->tipo, tipo);
        }
        else
        {
          strcpy(novo->tipo, "cliente");
        }
        strcpy(novo->email, email);
        strcpy(novo->password, pass);
        strcpy(novo->nome, nome);
        strcpy(novo->morada, morada);
        strcpy(novo->nif, nif);
        strcpy(novo->localizacao, localizacao);
        novo->saldo = 0;
        novo->seguinte = NULL;

        // percorrer a lista ligada até ao fim
        while (aux->seguinte != NULL)
        {
          aux = aux->seguinte;
        }

        // adicionar o novo utilizador no fim da lista ligada
        aux->seguinte = novo;

        printf("Conta criada com sucesso!\n");
        break;
      }
      else
      {
        printf("Não foi possível alocar memória\npara criação de um novo utilizador!\n");
      }
      break;
    }
    else if (emailExiste)
    {
      printf("\nJá existe uma conta com o email introduzido!\n");
      break;
    }
    else
      cod++;
  }
}
