#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "meio.h"
#include "../manager/fileManager.h"

// Ler meios do ficheiro
Meio *lerMeios()
{
  FILE *fp;
  int cod, id_cliente;
  float bat, aut, custo;
  char tipo[50], geoCode[100];
  time_t inicio_aluguer;
  Meio *aux = NULL;
  fp = fopen("./storage/meios.txt", "r");
  if (fp != NULL)
  {
    Meio *novo = malloc(sizeof(fp));
    if (novo != NULL)
    {
      printf("\nMeios disponíveis:\n");
      while (!feof(fp))
      {
        fscanf(fp, "%d;%[^;];%f;%f;%d;%f;%ld;%s\n", &cod, tipo, &bat, &aut, &id_cliente, &custo, &inicio_aluguer, geoCode);
        aux = inserirMeioFile(aux, cod, tipo, bat, aut, id_cliente, custo, inicio_aluguer, geoCode);
        novo = aux;
        printf("%d %s %.2f %.2f %d %.2f %ld %s\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia, aux->id_cliente, aux->custo, aux->inicio_aluguer, aux->geoCode);
      }
      fclose(fp);
    }
  }
  return (aux);
}

// Guardar meios no ficheiro
void guardarMeios(Meio *meios)
{
  FILE *fp;
  fp = fopen("./storage/meios.txt", "w");
  if (fp != NULL)
  {
    Meio *aux = meios;
    while (aux != NULL)
    {
      //TODO: escreve uma linha vazia antes de escrever os meios
      fprintf(fp, "%d;%s;%.2f;%.2f;%d;%.2f;%ld;%s\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia, aux->id_cliente, aux->custo, aux->inicio_aluguer, aux->geoCode);
      aux = aux->seguinte;
    }
    fclose(fp);
    printf("Guardado no ficheiro com sucesso!\n");
  }
  else
    printf("O ficheiro meios.txt não existe!\n");
}

// Inserção de um novo meio
void inserirMeio(Meio *meios)
{
  int cod = meios->codigo;
  char tipo[50], geoCode[100];
  float bateria, autonomia, custo;

  printf("\nTipo: ");
  scanf("%s", tipo);
  printf("Bateria: ");
  scanf("%f", &bateria);
  printf("Autonomia: ");
  scanf("%f", &autonomia);
  printf("Custo: ");
  scanf("%f", &custo);
  printf("GeoCode: ");
  scanf("%99[^\n]s", geoCode);
  getchar();

  while (1)
  {
    if (!existeMeio(meios, cod))
    {
      Meio *aux = meios;
      Meio *novo = malloc(sizeof(struct meios));
      if (novo != NULL)
      {
        novo->codigo = cod;
        strcpy(novo->tipo, tipo);
        novo->bateria = bateria;
        novo->autonomia = autonomia;
        novo->id_cliente = 0;
        novo->custo = custo;
        strcpy(novo->geoCode, geoCode);

        // percorrer a lista ligada até ao fim
        while (aux->seguinte != NULL)
        {
          aux = aux->seguinte;
        }

        // adicionar o novo meio no fim da lista ligada
        aux->seguinte = novo;
        printf("\nMeio criado com sucesso!\n");
        break;
      }
      else
      {
        printf("Não foi possível alocar memória\npara criação de um novo meio!\n");
      }
      break;
    }
    else
      cod++;
  }
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
    printf("| %-2d | %-12s | %06.2f%% |  %06.2fKm | %-7d |\n", meios->codigo, meios->tipo, meios->bateria, meios->autonomia, meios->id_cliente);
    meios = meios->seguinte;
  }
  printf("-----------------------------------------------------\n");
}

// Alterar um meio a partir do seu código
void alterarMeio(Meio *meios, int cod)
{
  Meio *aux = meios;
  aux = existeMeio(meios, cod);
  if (aux == NULL)
  {
    printf("Não existe nenhum meio com o código %d!\n", cod);
    return;
  }

  printf("\nTipo: ");
  scanf("%s", aux->tipo);
  printf("\nBateria: ");
  scanf("%f", &aux->bateria);
  printf("\nAutonomia: ");
  scanf("%f", &aux->autonomia);
  printf("\nCusto: ");
  scanf("%f", &aux->custo);
  printf("\nGeoCode: ");
  scanf("%s", aux->geoCode);

  printf("\n\nInformações do meio %d alteradas com sucesso!\n", cod);
}

// Remover um meio a partir do seu código
void removerMeio(Meio *meios, int cod)
{
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

// Determinar existência do 'codigo' na lista ligada 'meios'
// devolve 1 se existir ou 0 caso contrário
Meio *existeMeio(Meio *meios, int cod)
{
  while (meios != NULL)
  {
    if (meios->codigo == cod){
      return meios;
    }
    meios = meios->seguinte;
  }
  return (0);
}
