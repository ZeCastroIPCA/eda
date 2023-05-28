#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "conta.h"
#include "../../manager/fileManager.h"
#include "../../meios/meio.h"
#include "../../grafos/grafo.h"

// ler contas
Conta *lerContas()
{
  FILE *fp;
  int cod;
  float saldo;
  char tipo[50], email[50], pass[50], nome[50], morada[50], nif[9], localizacao[100];
  int meio_id;
  Conta *aux = NULL;
  fp = fopen("./storage/contas.txt", "r");
  if (fp != NULL)
  {
    Conta *novo = malloc(sizeof(fp));
    if (novo != NULL)
    {
      //printf("\nContas disponíveis:\n");
      while (!feof(fp))
      {
        fscanf(fp, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%f;%d;%s\n", &cod, tipo, email, pass, nome, morada, nif, &saldo, &meio_id, localizacao);
        aux = inserirContaFile(aux, cod, tipo, email, pass, nome, morada, nif, saldo, meio_id, localizacao);
        novo = aux;
        //printf("%d %s %s %s %s %s %s %.2f %d %s\n", aux->codigo, aux->tipo, aux->email, aux->password, aux->nome, aux->morada, aux->nif, aux->saldo, aux->meio_id, aux->localizacao);
      }
      fclose(fp);
    }
  }
  return (aux);
}

// guarda as contas em ficheiros de texto e binário
void guardarContas(Conta *contas)
{
  FILE *fp, *fpb;
  fp = fopen("./storage/contas.txt", "w+");
  fpb = fopen("./storage/contas.bin", "wb+");
  if (fp != NULL && fpb != NULL)
  {
    Conta *aux = contas;
    if (aux != NULL)
    {
      while (aux != NULL)
      {
        fprintf(fp, "%d;%s;%s;%s;%s;%s;%s;%f;%d;%s\n", aux->codigo, aux->tipo, aux->email, aux->password, aux->nome, aux->morada, aux->nif, aux->saldo, aux->meio_id, aux->localizacao);
        fprintf(fpb, "%d;%s;%s;%s;%s;%s;%s;%f;%d;%s\n", aux->codigo, aux->tipo, aux->email, aux->password, aux->nome, aux->morada, aux->nif, aux->saldo, aux->meio_id, aux->localizacao);
        aux = aux->seguinte;
      }
    }
    fclose(fp);
    fclose(fpb);
    printf("Guardado no ficheiro com sucesso!\n");
  }
  else
  {
    if (fp == NULL)
    {
      printf("O ficheiro contas.txt não existe!\n");
    }
    else if (fpb == NULL)
    {
      printf("O ficheiro contas.bin não existe!\n");
    }
    else
    {
      printf("Houve um erro na pesquisa dos ficheiros!\n");
    }
  }
}

// lista todas as contas de um determinado tipo (cliente ou gestor) conseguido por parâmetro
void listarContas(Conta *contas, char tipo[])
{
  if (tipo != NULL)
  {
    if (!strcmp(tipo, "cliente"))
    {
      printf("\n-- LISTA DE CLIENTES ------------------\n");
      printf("-------------------------------------------------------------------\n");
      printf("| ID | Nome       |  Saldo  | ID Meio | Localização               |\n");
      printf("-------------------------------------------------------------------\n");
      while (contas != NULL)
      {
        if (!strcmp(contas->tipo, "cliente"))
        {
          printf("| %-2d | %-10s | %6.2f€ | %-7d | %-25s |\n", contas->codigo, contas->nome, contas->saldo, contas->meio_id, contas->localizacao);
        }
        contas = contas->seguinte;
      }
      printf("-------------------------------------------------------------------\n");
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
        printf("---------------------------------------\n");
      }
    }
  }
}

// Alterar uma conta a partir do seu código
void alterarConta(Conta *contas, Grafo *grafo)
{
  int id;
  char geoCode[100];

  listarContas(contas, "cliente");

  printf("\nID a alterar:");
  scanf("%d", &id);

  Conta *aux = contas;
  aux = existeConta(contas, id);
  if (aux == NULL)
  {
    printf("Conta com ID %d não encontrada!\n", id);
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
  printf("GeoCode: ");
  scanf("%99s", geoCode);

  // Verificar se existe uma localização com o geocódigo inserido
  while (!existeVertice(grafo, geoCode))
  {
    printf("Não existe nenhuma localização com o geocódigo %s!\n", geoCode);
    printf("Insira um geocódigo válido:");
    scanf("%99s", geoCode);
  }
  // aux->localizacao = (char *)malloc(sizeof(char) * (strlen(geoCode) + 1));
  strcpy(aux->localizacao, geoCode);

  printf("\nInformações do cliente %d alteradas com sucesso!\n", id);
}

// Remove uma conta a partir do seu código
void removerConta(Conta *contas, int cod, int who)
{
  int conta_op;

  if (who == 1)
  {
    printf("\nTem a certeza que pretende apagar a sua conta?\nId: %d\n(1 - Sim | 0 - Não):", cod);
    scanf("%d", &conta_op);
    while (conta_op != 1 && conta_op != 0)
    {
      printf("\nOpção inválida! Tente novamente.\n");
      printf("\nTem a certeza que pretende apagar a sua conta?\nId: %d\n(1 - Sim | 0 - Não):", cod);
      scanf("%d", &conta_op);
    }
    if (conta_op == 0)
    {
      return;
    }
  }
  else
  {
    listarContas(contas, "cliente");
    printf("\nID a eliminar:");
    scanf("%d", &cod);
  }

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
    if (who == 1)
    {
      printf("\nA sua conta foi apagada com sucesso!\n");
    }
    else
    {
      printf("Conta com ID %d apagada com sucesso!\n", cod);
    }
    return;
  }
  while ((atual != NULL) && (atual->codigo != cod))
  {
    anterior = atual;
    atual = atual->seguinte;
  }
  if (atual == NULL)
  {
    if (who == 1)
    {
      printf("\nNão foi possível apagar a sua conta!\n");
    }
    else
    {
      printf("Conta com ID %d não encontrada!\n", cod);
    }
    return;
  }
  anterior->seguinte = atual->seguinte;
  free(atual);
  if (who == 1)
  {
    printf("\nA sua conta foi apagada com sucesso!\n");
  }
  else
  {
    printf("Conta com ID %d apagada com sucesso!\n", cod);
  }
}

void alugarMeio(Conta *contas, Conta *conta, Meio *meios, Grafo *grafo)
{
  int conta_op, aluguer_op, pesquisa_op, meio_cod, meiosNum = 0;

  // variável auxiliar da conta do cliente
  Conta *conta_aux = conta;

  // meio alugado pelo cliente
  Meio *meio = NULL;

  // encontrar o meio alugado pelo cliente
  Meio *meio_aux = meios;
  while (meio_aux != NULL)
  {
    if (meio_aux->id_cliente == conta_aux->codigo)
    {
      meio = meio_aux;
      break;
    }
    meio_aux = meio_aux->seguinte;
  }

  if (conta_aux->meio_id != 0)
  {
    printf("Pretente terminar o aluguer atual?\n(1 - Sim | 0 - Não):");
    scanf("%d", &aluguer_op);
    while (aluguer_op != 1 && aluguer_op != 0)
    {
      printf("\nOpção inválida! Tente novamente.\n");
      printf("Pretente terminar o aluguer atual?\n(1 - Sim | 0 - Não):");
      scanf("%d", &aluguer_op);
    }
    if (aluguer_op == 1)
    {
      conta_aux->meio_id = 0;
      meio->id_cliente = 0;
      int tempo_alugado = time(NULL) - meio->inicio_aluguer;
      conta_aux->saldo -= tempo_alugado * meio->custo;
      meio->inicio_aluguer = 0;
      printf("\nAluguer terminado com sucesso!\n");
    }
    else
    {
      printf("\nO aluguer do meio %d não foi terminado!\n", conta_aux->meio_id);
    }
    return;
  }
  printf("Como pretente pesquisar?\n(1 - Pesquisar por Raio | 2 - Pesquisar por Autonomia):");
  scanf("%d", &pesquisa_op);
  while (pesquisa_op != 1 && pesquisa_op != 2)
  {
    printf("\nOpção inválida! Tente novamente.\n");
    printf("Como pretente pesquisar?\n(1 - Pesquisar por Raio | 2 - Pesquisar por Autonomia):");
    scanf("%d", &pesquisa_op);
  }
  if (pesquisa_op == 1)
  {
    int raio;
    char tipo[50];
    printf("Qual o raio da pesquisa?\nRaio:");
    scanf("%d", &raio);
    printf("Qual o tipo de meio que pretende alugar?\nTipo:");
    scanf("%s", tipo);
    meiosNum = listarMeiosPorRaio(conta, grafo, meios, raio, tipo);
  }
  else
  {
    meiosNum = listarMeiosParaCliente(meios);
  }
  if (meiosNum == 0)
  {
    printf("\nNão existem meios disponíveis para alugar!\n\n");
    return;
  }
  if (meiosNum > 0)
  {
    printf("Qual o meio que pretende alugar?\nSerão debitados da sua conta 0,5€\nID do meio:");
    scanf("%d", &meio_cod);
  }
  if (conta_aux->saldo < 0.5)
  {
    printf("\nNão tem saldo suficiente para alugar um meio!\n");
    return;
  }
  else if (existeMeio(meios, meio_cod))
  {
    conta_aux->meio_id = meio_cod;
    meio = existeMeio(meios, meio_cod);
    meio->id_cliente = conta_aux->codigo;
    meio->inicio_aluguer = time(NULL);
    conta_aux->saldo -= 0.5;
    printf("\nMeio alugado com sucesso!\n");
    return;
  }
  printf("\nO meio que pretende alugar não existe!\n");
  return;
}

// Carregar saldo na conta
void carregarSaldo(Conta *conta)
{
  float saldoCarregar;

  Conta *aux = conta;

  printf("Carregar saldo:");
  scanf("%f", &saldoCarregar);

  aux->saldo += saldoCarregar;

  printf("\nSaldo carregado com sucesso!\n");
}

// Determinar existência do 'codigo' na lista ligada 'contas'
// devolve o código do último registo + 1 (ou seja, o próximo a ser registado) se existir ou 0 caso contrário
Conta *existeConta(Conta *contas, int cod)
{
  while (contas != NULL)
  {
    if (contas->codigo == cod)
    {
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
