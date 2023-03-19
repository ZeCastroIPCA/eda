#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conta.h"
#include "../manager/fileManager.h"

// ler contas
Conta *lerContas()
{
  FILE *fp;
  int cod;
  float saldo;
  char tipo[50], email[50], pass[50], nome[50], morada[50], nif[9];
  int renting;
  Conta *aux = NULL;
  fp = fopen("./storage/contas.txt", "r");
  if (fp != NULL)
  {
    Conta *novo = malloc(sizeof(fp));
    if (novo != NULL)
    {
      // printf("Contas disponíveis:\n");
      while (!feof(fp))
      {
        fscanf(fp, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%f;%d \n", &cod, tipo, email, pass, nome, morada, nif, &saldo, &renting);
        aux = inserirContaFile(aux, cod, tipo, email, pass, nome, morada, nif, saldo, renting);
        novo = aux;
        // printf("%d %s %s %s %s %s %s %.2f %d\n", aux->codigo, aux->tipo, aux->email, aux->password, aux->nome, aux->morada, aux->nif, aux->saldo, aux->renting);
      }
      fclose(fp);
    }
  }
  return (aux);
}
// Remover uma conta a partir do seu código
void removerConta(Conta *inicio, int cod)
{
  Conta *anterior = inicio, *atual = inicio, *aux;
  if (atual == NULL)
  {
    printf("Não existem contas registadas!\n");
    return 0;
  }
  if (atual->codigo == cod) // remoção do 1º registo
  {
    aux = atual->seguinte;
    free(atual);
    return 0;
  }
  while ((atual != NULL) && (atual->codigo != cod))
  {
    anterior = atual;
    atual = atual->seguinte;
  }
  if (atual == NULL)
  {
    printf("Conta não encontrada!\n");
    return 0;
  }
  anterior->seguinte = atual->seguinte;
  free(atual);
}

// guardar contas no ficheiro
void guardarContas(Conta *inicio)
{
  FILE *fp;
  fp = fopen("./storage/contas.txt", "w");
  if (fp != NULL)
  {
    Conta *aux = inicio;
    if (aux != NULL)
    {
      while (aux != NULL)
      {
        fprintf(fp, "%d;%s;%s;%s;%s;%s;%s;%f;%d\n", aux->codigo, aux->tipo, aux->email, aux->password, aux->nome, aux->morada, aux->nif, aux->saldo, aux->renting);
        aux = aux->seguinte;
      }
    }
    fclose(fp);
    printf("Guardado no ficheiro com sucesso!\n");
  }
  else
    printf("O ficheiro contas.txt não existe!\n");
}

void listarContas(Conta *contas)
{
  printf("\n-- LISTA DE CLIENTES ------------------\n");
  printf("---------------------------------------\n");
  printf("| ID | Nome         | Saldo | Aluguer |\n");
  printf("---------------------------------------\n");
  while (contas != NULL)
  {
    if (!strcmp(contas->tipo, "cliente"))
    {
      printf("| %-2d | %-12s | %05.2f | %-7d |\n", contas->codigo, contas->nome, contas->saldo, contas->renting);
    }
    contas = contas->seguinte;
  }
  printf("---------------------------------------\n");
}

// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve o código do último registo + 1 (ou seja, o próximo a ser registado) se existir ou 0 caso contrário
int existeConta(Conta *contas, int cod)
{
  while (contas != NULL)
  {
    if (contas->codigo == cod)
      return (contas->codigo + 1);
    contas = contas->seguinte;
  }
  return (0);
}
