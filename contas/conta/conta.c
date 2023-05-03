#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conta.h"
#include "../../manager/fileManager.h"
#include "../../meios/meio.h"

// ler contas
Conta *lerContas()
{
  FILE *fp;
  int cod;
  float saldo;
  char tipo[50], email[50], pass[50], nome[50], morada[50], nif[9];
  int meio_id;
  Conta *aux = NULL;
  fp = fopen("./storage/contas.txt", "r");
  if (fp != NULL)
  {
    Conta *novo = malloc(sizeof(fp));
    if (novo != NULL)
    {
      printf("\nContas disponíveis:\n");
      while (!feof(fp))
      {
        fscanf(fp, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%f;%d \n", &cod, tipo, email, pass, nome, morada, nif, &saldo, &meio_id);
        aux = inserirContaFile(aux, cod, tipo, email, pass, nome, morada, nif, saldo, meio_id);
        novo = aux;
        printf("%d %s %s %s %s %s %s %.2f %d\n", aux->codigo, aux->tipo, aux->email, aux->password, aux->nome, aux->morada, aux->nif, aux->saldo, aux->meio_id);
      }
      fclose(fp);
    }
  }
  return (aux);
}

// guarda as contas em ficheiros de texto e binário
void guardarContas(Conta *contas)
{
  FILE *fp;
  fp = fopen("./storage/contas.txt", "w");
  if (fp != NULL)
  {
    Conta *aux = contas;
    if (aux != NULL)
    {
      while (aux != NULL)
      {
        fprintf(fp, "%d;%s;%s;%s;%s;%s;%s;%f;%d\n", aux->codigo, aux->tipo, aux->email, aux->password, aux->nome, aux->morada, aux->nif, aux->saldo, aux->meio_id);
        aux = aux->seguinte;
      }
    }
    fclose(fp);
    printf("Guardado no ficheiro com sucesso!\n");
  }
  else
    printf("O ficheiro contas.txt não existe!\n");
}

// lista todas as contas de um determinado tipo (cliente ou gestor) conseguido por parâmetro
void listarContas(Conta *contas, char tipo[])
{
  if (tipo != NULL)
  {
    if (!strcmp(tipo, "cliente"))
    {
      printf("\n-- LISTA DE CLIENTES ------------------\n");
      printf("---------------------------------------\n");
      printf("| ID | Nome         | Saldo | ID Meio |\n");
      printf("---------------------------------------\n");
      while (contas != NULL)
      {
        if (!strcmp(contas->tipo, "cliente"))
        {
          printf("| %-2d | %-12s | %05.2f | %-7d |\n", contas->codigo, contas->nome, contas->saldo, contas->meio_id);
        }
        contas = contas->seguinte;
      }
    }
    else
    {
      printf("\n-- LISTA DE GESTORES ------------------\n");
      printf("---------------------------------------\n");
      printf("| ID | Email                          |\n");
      printf("---------------------------------------\n");
      while (contas != NULL)
      {
        if (!strcmp(contas->tipo, "gestor"))
        {
          printf("| %-2d | %-30s |\n", contas->codigo, contas->email);
        }
        contas = contas->seguinte;
      }
    }
  }
  printf("---------------------------------------\n");
}

// Alterar uma conta a partir do seu código
void alterarConta(Conta *contas, int cod)
{
  Conta *aux = contas;
  aux = existeConta(contas, cod);
  if (aux == NULL)
  {
    printf("Conta com ID %d não encontrada!\n", cod);
    return;
  }

  printf("\nEmail: ");
  scanf("%s", aux->email);
  printf("Password: ");
  scanf("%s", aux->password);
  printf("Nome: ");
  scanf("%s", aux->nome);
  printf("Morada: ");
  scanf("%s", aux->morada);
  printf("NIF: ");
  scanf("%s", aux->nif);
  printf("Saldo: ");
  scanf("%f", &aux->saldo);

  printf("\nInformações do cliente %d alteradas com sucesso!\n", cod);
}

// Remove uma conta a partir do seu código
void removerConta(Conta *contas, int cod)
{
  Conta *anterior = contas, *atual = contas, *aux;
  if (atual == NULL)
  {
    printf("Não existem contas registadas!\n");
    return;
  }
  if (atual->codigo == cod) // remoção do 1º registo
  {
    aux = atual->seguinte;
    free(atual);
    return;
  }
  while ((atual != NULL) && (atual->codigo != cod))
  {
    anterior = atual;
    atual = atual->seguinte;
  }
  if (atual == NULL)
  {
    printf("Conta não encontrada!\n");
    return;
  }
  anterior->seguinte = atual->seguinte;
  free(atual);
}

// Determinar existência do 'codigo' na lista ligada 'contas'
// devolve o código do último registo + 1 (ou seja, o próximo a ser registado) se existir ou 0 caso contrário
Conta *existeConta(Conta *contas, int cod)
{
  while (contas != NULL)
  {
    if (contas->codigo == cod){
      return contas;
    }
    contas = contas->seguinte;
  }
  return (0);
}

// Determinar existência do 'email' inserido na lista ligada 'contas'
int verificarEmail(Conta *contas, char email[])
{
  while (contas != NULL)
  {
    if (!strcmp(contas->email, email))
      return (1);
    contas = contas->seguinte;
  }
  return (0);
}
