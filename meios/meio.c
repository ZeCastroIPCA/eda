#include <stdlib.h>
#include <string.h>
#include "meio.h"

int guardarMeios(Meio *meios)
{
  int cod;
  float bat, aut;
  char tipo[50];
  FILE *fpw, *fpr;
  fpw = fopen("./storage/meios.txt", "w");
  fpr = fopen("./storage/meios.txt", "r");
  if (fpw != NULL && fpr != NULL)
  {
    Meio *aux = meios;
    while (aux != NULL)
    {

      fprintf(fpw, "%d;%.2f;%.2f;%s\n", aux->codigo, aux->bateria,
              aux->autonomia, aux->tipo);
      aux = aux->seguinte;
    }
    fclose(fpw);
    fclose(fpr);
    return (1);
  }
  else
    return (0);
}

Meio *lerMeios()
{
  FILE *fp;
  int cod;
  float bat, aut;
  char tipo[50];
  int c;
  Meio *aux = NULL;
  fp = fopen("./storage/meios.txt", "r");
  if (fp != NULL)
  {
    Meio *novo = malloc(sizeof(fp));
    if (novo != NULL)
    {
      while (!feof(fp))
      {
        fscanf(fp, "%d;%f;%f;%s\n", &cod, &bat, &aut, tipo);
        aux = inserirMeio(aux, cod, tipo, bat, aut);
        novo = aux;
        // printf("Meios: %d %s %.2f %.2f\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia);
      }
      fclose(fp);
    }
  }
  return (aux);
}

// Inserção de um novo registo
Meio *inserirMeio(Meio *meios, int cod, char tipo[], float bat, float aut)
{
  if (!existeMeio(meios, cod))
  {
    Meio *novo = malloc(sizeof(struct registo));
    if (novo != NULL)
    {
      novo->codigo = cod;
      strcpy(novo->tipo, tipo);
      novo->bateria = bat;
      novo->autonomia = aut;
      novo->seguinte = meios;
      return (novo);
    }
    else
    {
      return (meios);
    }
  }
  else
    return (meios);
}

// Listagem de todos os meios numa tabela formatada
void listarMeios(Meio *meios)
{
  printf("\n--  LISTA DE MEIOS   --------------------------------\n");
  printf("-----------------------------------------------------\n");
  printf("| ID | Tipo         | Bateria | Autonomia | Alugado |\n");
  printf("-----------------------------------------------------\n");
  while (meios != NULL)
  {

    printf("| %-2d | %-12s |  %05.2f%% |  %05.2fKm  | ------- |\n", meios->codigo, meios->tipo, meios->bateria, meios->autonomia);
    meios = meios->seguinte;
  }
  printf("-----------------------------------------------------\n");
}

// Determinar existência do 'codigo' na lista ligada 'meios'
// devolve 1 se existir ou 0 caso contrário
int existeMeio(Meio *meios, int cod)
{
  while (meios != NULL)
  {
    if (meios->codigo == cod)
      return (1);
    meios = meios->seguinte;
  }
  return (0);
}

/*
Meio* removerMeio(Meio* meios, int cod) // Remover um meio a partir do seu código
{while (meios!=NULL)
 {if (meios->codigo==cod)
   {aux = meios->seguinte;
          free(meios);
    return(aux);
   }
  else {meios = removerMeio(meios->seguinte,cod);
  return(meios);
       }
 }
}
*/

// Remover um meio a partir do seu código
void removerMeio(Meio *meios, int cod)
{
  // TODO - bug fix: ao remover o meio no mesmo ciclo em que cria o meio, vai guardar lixo
  Meio *anterior = meios, *atual = meios, *aux;
  if (atual == NULL)
  {
    printf("Não existem meios registados!\n");
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
    printf("Meio não encontrado!\n");
    return;
  }
  anterior->seguinte = atual->seguinte;
  free(atual);
}
