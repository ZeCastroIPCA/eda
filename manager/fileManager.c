#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../contas/conta/conta.h"
#include "fileManager.h"

// inserir conta no ficheiro
Conta *inserirContaFile(Conta *inicio, int cod, char tipo[], char email[], char pass[], char nome[], char morada[], char nif[], float saldo, int renting)
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
      novo->renting = 0;
      novo->seguinte = inicio;
      return (novo);
    }
    
    return (inicio);
  }
  

  return (inicio);
}