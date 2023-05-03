#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../contas/conta/conta.h"
#include "../meios/meio.h"
#include "fileManager.h"

// inserir conta no ficheiro
Conta *inserirContaFile(Conta *contas, int cod, char tipo[], char email[], char pass[], char nome[], char morada[], char nif[], float saldo, int meio_id)
{
  if (!existeConta(contas, cod))
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
        novo->meio_id = meio_id;
      }
      else
      {
        strcpy(novo->nome, "n/a");
        strcpy(novo->morada, "n/a");
        strcpy(novo->nif, "n/a");
        novo->saldo = 0;
        novo->meio_id = 0;
      }

      novo->seguinte = contas;
      return (novo);
    }
    
    return (contas);
  }

  return (contas);
}

// inserir conta no ficheiro binário
int saveContasBin(Conta *contas)
{
  FILE *fp;
  fp = fopen("./storagebin/contas.bin", "wb");
  if (fp != NULL)
  {
    Conta *aux = contas;
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

// inserir meios no ficheiro
Meio *inserirMeioFile(Meio *meios, int cod, char tipo[], float bateria, float autonomia, int id_cliente, float custo, time_t inicio_aluguer, char geoCode[])
{
  if (!existeMeio(meios, cod))
  {
    Meio *novo = malloc(sizeof(struct meios));
    if (novo != NULL)
    {
      novo->codigo = cod;
      strcpy(novo->tipo, tipo);
      novo->bateria = bateria;
      novo->autonomia = autonomia;
      novo->id_cliente = id_cliente;
      novo->custo = custo;
      novo->inicio_aluguer = inicio_aluguer;
      strcpy(novo->geoCode, geoCode);

      novo->seguinte = meios;
      return (novo);
    }
    
    return (meios);
  }

  return (meios);
}