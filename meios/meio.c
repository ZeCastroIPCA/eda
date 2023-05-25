#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "meio.h"

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
        fscanf(fp, "%d;%[^;];%f;%f;%d;%f;%ld\n", &cod, tipo, &bat, &aut, &id_cliente, &custo, &inicio_aluguer);
        aux = inserirMeioFile(aux, cod, tipo, bat, aut, id_cliente, custo, inicio_aluguer);
        novo = aux;
        printf("%d %s %.2f %.2f %d %.2f %ld\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia, aux->id_cliente, aux->custo, aux->inicio_aluguer);
      }
      fclose(fp);
    }
  }
  return (aux);
}

// Guardar meios no ficheiro
void guardarMeios(Meio *meios)
{
  FILE *fp, *fpb;
  fp = fopen("./storage/meios.txt", "w+");
  fpb = fopen("./storage/meios.bin", "wb+");
  if (fp != NULL)
  {
    Meio *aux = meios;
    while (aux != NULL)
    {
      fprintf(fp, "%d;%s;%.2f;%.2f;%d;%.2f;%ld\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia, aux->id_cliente, aux->custo, aux->inicio_aluguer);
      fprintf(fpb, "%d;%s;%.2f;%.2f;%d;%.2f;%ld\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia, aux->id_cliente, aux->custo, aux->inicio_aluguer);
      aux = aux->seguinte;
    }
    fclose(fp);
    fclose(fpb);
    printf("Guardado no ficheiro com sucesso!\n");
  }
  else
  {
    if (fp == NULL)
    {
      printf("O ficheiro meios.txt não existe!\n");
    }
    else if (fpb == NULL)
    {
      printf("O ficheiro meios.bin não existe!\n");
    }
    else
    {
      printf("Houve um erro na pesquisa dos ficheiros!\n");
    }
  }
}

// Inserir meio de transporte e adicionar localização com geocódigo no grafo
void inserirMeio(Meio *meios, Grafo *grafo)
{
  int cod = meios->codigo;
  char tipo[50], geoCode[100];
  float bateria, autonomia, custo;

  printf("\nTipo: ");
  scanf("%49s", tipo);
  printf("Bateria: ");
  scanf("%f", &bateria);
  printf("Autonomia: ");
  scanf("%f", &autonomia);
  printf("Custo: ");
  scanf("%f", &custo);
  printf("GeoCode: ");
  scanf("%99s", geoCode);

  // Verificar se existe uma localização com o geocódigo inserido
  while (!existeVertice(*grafo, geoCode))
  {
    printf("Não existe nenhuma localização com o geocódigo %s!\n", geocodigo);
    printf("Insira um geocódigo válido:");
    scanf("%99s", geoCode);
  }

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

        // percorrer a lista ligada do meio até ao fim 
        while (aux->seguinte != NULL)
        {
          aux = aux->seguinte;
        }

        // adicionar o novo meio no fim da lista ligada do meio
        aux->seguinte = novo;

        // percorrer a lista ligada do grafo até ao fim
        while (*grafo->meios->seguinte != NULL)
        {
          *grafo = *grafo->meios->seguinte;
        }

        // adicionar o novo meio no fim da lista ligada do grafo
        *grafo->meios = novo;
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

// Inserção de um novo meio
void inserirMeio(Meio *meios)
{
  int cod = meios->codigo;
  char tipo[50], geoCode[100];
  float bateria, autonomia, custo;

  printf("\nTipo: ");
  scanf("%49s", tipo);
  printf("Bateria: ");
  scanf("%f", &bateria);
  printf("Autonomia: ");
  scanf("%f", &autonomia);
  printf("Custo: ");
  scanf("%f", &custo);
  printf("GeoCode: ");
  scanf("%99s", geoCode);

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
    printf("| %-2d | %-12s | %6.2f%% |  %6.2fKm | %-7d |\n", meios->codigo, meios->tipo, meios->bateria, meios->autonomia, meios->id_cliente);
    meios = meios->seguinte;
  }
  printf("-----------------------------------------------------\n");
}

// Listagem de todos os meios por ordem decrescente de autonomia
void listarMeiosParaCliente(Meio *meios)
{
  // Contar o número de meios
  int count = 0;
  Meio *aux = meios;
  while (aux != NULL)
  {
    count++;
    aux = aux->seguinte;
  }

  // Criar um array de meios para poder ordenar
  Meio **meios_array = malloc(count * sizeof(Meio *));
  aux = meios;
  int i = 0;
  while (aux != NULL)
  {
    meios_array[i] = aux;
    aux = aux->seguinte;
    i++;
  }

  // Ordenar o array por ordem decrescente de autonomia
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = i + 1; j < count; j++)
    {
      if (meios_array[i]->autonomia < meios_array[j]->autonomia)
      {
        Meio *aux = meios_array[i];
        meios_array[i] = meios_array[j];
        meios_array[j] = aux;
      }
    }
  }

  // Imprimir a tabela
  printf("\n--  LISTA DE MEIOS   --------------------------------\n");
  printf("-----------------------------------------------------\n");
  printf("| ID | Tipo         | Bateria | Autonomia |  €/seg  |\n");
  printf("-----------------------------------------------------\n");
  for (int i = 0; i < count; i++)
  {
    Meio *meio = meios_array[i];
    if (meio->id_cliente == 0)
    {
      printf("| %-2d | %-12s | %6.2f%% |  %6.2fKm |  %4.2f€  |\n", meio->codigo, meio->tipo, meio->bateria, meio->autonomia, meio->custo);
    }
  }
  printf("-----------------------------------------------------\n");

  // Libertar a memória alocada para o array
  free(meios_array);
}

// Listagem de meios por geocode
void listarMeiosPorGeoCode(Meio *meios)
{
  char geo[100];
  int count = 0;

  printf("\nGeo Código:");
  scanf("%99s", geo);

  printf("\n---  LISTA DE MEIOS EM %s  ---\n", geo);
  printf("-----------------------------------------------------\n");
  printf("| ID | Tipo         | Bateria | Autonomia | Geocode |\n");
  printf("-----------------------------------------------------\n");
  while (meios != NULL)
  {
    if (strcmp(meios->geoCode, geo) == 0)
    {
      printf("| %-2d | %-12s | %6.2f%% |  %6.2fKm | %-7s |\n", meios->codigo, meios->tipo, meios->bateria, meios->autonomia, meios->geoCode);
      count++;
    }
    meios = meios->seguinte;
  }
  if (meios == NULL && count == 0)
  {
    printf("|     Não existem meios no Geo Código %-9s     |\n", geo);
  }
  printf("-----------------------------------------------------\n");
}

// Alterar um meio a partir do seu código
void alterarMeio(Meio *meios)
{
  int id;

  listarMeios(meios);

  printf("\nID a alterar:");
  scanf("%d", &id);

  Meio *aux = NULL;
  aux = existeMeio(meios, id);
  if (aux == NULL)
  {
    printf("Não existe nenhum meio com o código %d!\n", id);
    return;
  }

  printf("\nTipo: ");
  scanf("%s", aux->tipo);
  printf("Bateria: ");
  scanf("%f", &aux->bateria);
  printf("Autonomia: ");
  scanf("%f", &aux->autonomia);
  printf("Custo: ");
  scanf("%f", &aux->custo);
  printf("GeoCode: ");
  scanf("%s", aux->geoCode);

  printf("\nInformações do meio %d alteradas com sucesso!\n", id);
}

// Remover um meio a partir do seu código
void removerMeio(Meio *meios)
{
  int id;

  listarMeios(meios);

  printf("\nID a eliminar:");
  scanf("%d", &id);

  Meio *anterior = meios, *atual = meios, *aux;
  if (atual == NULL)
  {
    printf("Não existem meios registados!\n");
    return;
  }
  if (atual->codigo == id) // remoção do 1º registo
  {
    aux = atual->seguinte;
    free(atual);
    printf("\nO meio %d foi apagado com sucesso!\n", id);
    return;
  }
  while ((atual != NULL) && (atual->codigo != id))
  {
    anterior = atual;
    atual = atual->seguinte;
  }
  if (atual == NULL)
  {
    printf("\nO meio %d não foi apagado!\n", id);
    return;
  }
  anterior->seguinte = atual->seguinte;
  free(atual);
  printf("\nO meio %d foi apagado com sucesso!\n", id);
}

// Determinar existência do 'codigo' na lista ligada 'meios'
Meio *existeMeio(Meio *meios, int cod)
{
  while (meios != NULL)
  {
    if (meios->codigo == cod)
    {
      return meios;
    }
    meios = meios->seguinte;
  }
  return (0);
}
