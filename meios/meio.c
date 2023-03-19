#include <stdlib.h>
#include <string.h>
#include "meio.h"

int guardarMeios(Meio *inicio)
{
  int cod;
  float bat, aut;
  char tipo[50];
  FILE *fpw, *fpr;
  fpw = fopen("./storage/meios.txt", "w");
  fpr = fopen("./storage/meios.txt", "r");
  if (fpw != NULL && fpr != NULL)
  {
    Meio *aux = inicio;
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
        printf("Meios: %d %s %.2f %.2f\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia);
      }
      fclose(fp);
    }
  }
  return (aux);
}

// Inserção de um novo registo
Meio *inserirMeio(Meio *inicio, int cod, char tipo[], float bat, float aut)
{
  if (!existeMeio(inicio, cod))
  {
    Meio *novo = malloc(sizeof(struct registo));
    if (novo != NULL)
    {
      novo->codigo = cod;
      strcpy(novo->tipo, tipo);
      novo->bateria = bat;
      novo->autonomia = aut;
      novo->seguinte = inicio;
      return (novo);
    } else {
      return (inicio);
    }
  }
  else
    return (inicio);
}

// listar na consola o conteúdo da lista ligada
void listarMeios(Meio *inicio)
{
  while (inicio != NULL)
  {
    printf("%d %s %.2f %.2f\n", inicio->codigo, inicio->tipo,
           inicio->bateria, inicio->autonomia);
    inicio = inicio->seguinte;
  }
}

// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve 1 se existir ou 0 caso contrário
int existeMeio(Meio *inicio, int cod)
{
  while (inicio != NULL)
  {
    if (inicio->codigo == cod)
      return (1);
    inicio = inicio->seguinte;
  }
  return (0);
}

/*
Meio* removerMeio(Meio* inicio, int cod) // Remover um meio a partir do seu código
{while (inicio!=NULL)
 {if (inicio->codigo==cod)
   {aux = inicio->seguinte;
          free(inicio);
    return(aux);
   }
  else {inicio = removerMeio(inicio->seguinte,cod);
  return(inicio);
       }
 }
}
*/

// Remover um meio a partir do seu código{
Meio *removerMeio(Meio *inicio, int cod)
{
  Meio *anterior = inicio, *atual = inicio, *aux;

  if (atual == NULL)
    return (NULL);
  else if (atual->codigo == cod) // remoção do 1º registo
  {
    aux = atual->seguinte;
    free(atual);
    return (aux);
  }
  else
  {
    while ((atual != NULL) && (atual->codigo != cod))
    {
      anterior = atual;
      atual = atual->seguinte;
    }
    if (atual == NULL)
      return (inicio);
    else
    {
      anterior->seguinte = atual->seguinte;
      free(atual);
      return (inicio);
    }
  }
}
