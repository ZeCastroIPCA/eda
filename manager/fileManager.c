#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../contas/conta/conta.h"
#include "fileManager.h"

// inserir conta no ficheiro
Conta *inserirContaFile(Conta *inicio, int cod, char tipo[], char email[], char pass[], char nome[], char morada[], char nif[], float saldo, int meio_id)
{
  if (!existeConta(inicio, cod))
  {
    Conta *novo = malloc(sizeof(struct contas));
    if (novo != NULL)
    {
      novo->codigo = cod;
      strcpy(novo->tipo, tipo);
      strcpy(novo->email, email);
      strcpy(novo->password, pass);
      if (strcmp(novo->tipo, "cliente") == 0)
      {
        strcpy(novo->nome, nome);
        strcpy(novo->morada, morada);
        strcpy(novo->nif, nif);
        novo->saldo = saldo;
      }
      else
      {
        strcpy(novo->nome, "n/a");
        strcpy(novo->morada, "n/a");
        strcpy(novo->nif, "n/a");
        novo->saldo = 0;
      }
      novo->meio_id = 0;
      novo->seguinte = inicio;
      return (novo);
    }
    
    return (inicio);
  }
  

  return (inicio);
}

int saveContasBin(Conta *inicio)
{
  FILE *fp;
  fp = fopen("./storagebin/contas.bin", "wb");
  if (fp != NULL)
  {
    Conta *aux = inicio;
    while (aux != NULL)
    {
      fprintf(fp, "%d;%s;%s;%s;%s;%s;%s;%f;%d\n", aux->codigo, aux->tipo, aux->email, aux->password, aux->nome, aux->morada, aux->nif, aux->saldo, aux->meio_id);
      aux = aux->seguinte;
    }
    fclose(fp);
    return (1);
  }
  else
    return (0);
}