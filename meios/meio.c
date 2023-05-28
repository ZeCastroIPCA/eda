#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "meio.h"
#include "../manager/fileManager.h"
#include "../grafos/grafo.h"
#include "../contas/conta/conta.h"

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
      printf("%d %s %.2f %.2f %d %.2f %ld\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia, aux->id_cliente, aux->custo, aux->inicio_aluguer);
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
void inserirMeio(Meio **meios, Grafo **grafo)
{
  // TODO - Corrigir bug de quando grava novo meio, não grava no ficheiro, no grafo.txt apaga todos do mesmo geocodigo e no meios.txt não chega a gravar
  int cod = (*meios)->codigo + 1;
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
    printf("Não existe nenhuma localização com o geocódigo %s!\n", geoCode);
    printf("Insira um geocódigo válido:");
    scanf("%99s", geoCode);
  }

  while (existeMeio(*meios, cod))
  {
    cod++;
  }

  Meio *novo = malloc(sizeof(struct meios));
  if (novo != NULL)
  {
    novo->codigo = cod;
    strcpy(novo->tipo, tipo);
    novo->bateria = bateria;
    novo->autonomia = autonomia;
    novo->id_cliente = 0;
    novo->custo = custo;

    // Procurar o vértice com o geocódigo inserido
    Grafo *grafoAux = *grafo;
    while (strcmp(grafoAux->vertice, geoCode) != 0)
    {
      grafoAux = grafoAux->seguinte;
    }

    // Adicionar o novo meio no início da lista ligada do grafo
    novo->seguinte = grafoAux->meios;
    grafoAux->meios = novo;
  }
  else
  {
    printf("Não foi possível alocar memória\npara criação de um novo meio!\n");
    return;
  }
  // Criar uma cópia do novo meio
  Meio *novo_meio = malloc(sizeof(struct meios));
  *novo_meio = *novo;
  if (novo_meio != NULL)
  {
    novo_meio->codigo = cod;
    strcpy(novo_meio->tipo, tipo);
    novo_meio->bateria = bateria;
    novo_meio->autonomia = autonomia;
    novo_meio->id_cliente = 0;
    novo_meio->custo = custo;

    // Adicionar o novo meio no início da lista ligada dos meios
    novo_meio->seguinte = *meios;
    *meios = novo_meio;
  }
  else
  {
    printf("Não foi possível alocar memória para criação de um novo meio!\n");
    return;
  }
  printf("\nMeio criado com sucesso!\n");
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
int listarMeiosParaCliente(Meio *meios)
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
  return count;
}

// Listagem de meios por geocode
void listarMeiosPorGeoCode(Grafo **grafo)
{
  char geo[100];
  int count = 0;

  printf("\nGeo Código:");
  scanf("%99s", geo);

  printf("\n---  LISTA DE MEIOS EM %s  ---\n", geo);
  printf("-----------------------------------------------------------------------\n");
  printf("| ID | Tipo         | Bateria | Autonomia | Geocode                   |\n");
  printf("-----------------------------------------------------------------------\n");

  Grafo *grafoAux = *grafo;
  while (grafoAux != NULL)
  {
    Meio *meiosAux = grafoAux->meios;
    while (meiosAux != NULL)
    {
      if (strcmp(grafoAux->vertice, geo) == 0)
      {
        printf("| %-2d | %-12s | %6.2f%% |  %6.2fKm | %-25s |\n", meiosAux->codigo, meiosAux->tipo, meiosAux->bateria, meiosAux->autonomia, grafoAux->vertice);
        count++;
      }
      meiosAux = meiosAux->seguinte;
    }
    grafoAux = grafoAux->seguinte;
  }

  if (count == 0)
  {
    printf("|        Não existem meios no Geo Código %-20s         |\n", geo);
  }
  printf("-----------------------------------------------------------------------\n");
}


// Listagem de meios por raio
int listarMeiosPorRaio(Conta *conta, Grafo *grafo, Meio *meios, float raio, char tipo[])
{
  int count = 0;

  printf("\n---  LISTA DE %s ATÉ %.0fm DE %s  ---\n", tipo, raio, conta->localizacao);
  printf("-----------------------------------------------------------------------------------\n");
  printf("| ID | Tipo         | Bateria | Autonomia | Geocode                   | Distância |\n");
  printf("-----------------------------------------------------------------------------------\n");

  // Percorrer o grafo e listar os meios que estão dentro do raio e que são do tipo pretendido
  pesquisaRaio(grafo, meios, conta->localizacao, raio, tipo, 0);

  return 1;
}

// Alterar um meio a partir do seu código
void alterarMeio(Meio *meios, Grafo *grafo)
{
  int id;

  char geocode[100];

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
  do
  {
    printf("Geo Código: ");
    scanf("%s", geocode);
    if (existeVertice(grafo, geocode))
    {
      // TODO - Alterar o geocode do meio e remover o vértice do grafo
      //  Remover o meio do grafo e voltar a inserir no novo grafo
      Grafo *grafoAux = grafo;
      Meio *meioAux = grafoAux->meios;
      while (grafoAux != NULL)
      {
        printf("Vertice: %s\n", grafoAux->vertice);
        while (meioAux != NULL && meioAux->codigo != id)
        {
          printf("Meio: %d %s\n", meioAux->codigo, meioAux->tipo);
          // Remover o meio do grafo
          removerMeioGrafo(&grafo, id);
          // Inserir o meio no novo grafo
          adicionarMeioMan(&grafo, meios, geocode, id);
          printf("\nInformações do meio %d alteradas com sucesso!\n", id);
          return;
          meioAux = meioAux->seguinte;
        }
        grafoAux = grafoAux->seguinte;
      }
    }
  } while (!existeVertice(grafo, geocode));

  printf("\nErro na remoção do meio %d!\n", id);
}

// Remover um meio a partir do seu código
void removerMeio(Meio **meios, Grafo **grafo)
{
  int id;

  listarMeios(*meios);

  printf("\nID a eliminar:");
  scanf("%d", &id);

  Meio *anterior = NULL, *atual = *meios;

  if (atual == NULL)
  {
    printf("Não existem meios registados!\n");
    return;
  }

  if (atual->codigo == id) // Remoção do 1º registo
  {
    *meios = atual->seguinte;
    free(atual);
    printf("\nO meio %d foi apagado com sucesso!\n", id);
  }
  else
  {
    while (atual != NULL && atual->codigo != id)
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

  // Update the meios list in the graph
  Grafo *grafoAux = *grafo;
  while (grafoAux != NULL)
  {
    Meio *meioAtual = grafoAux->meios;
    Meio *meioAnterior = NULL;

    while (meioAtual != NULL)
    {
      if (meioAtual->codigo == id)
      {
        if (meioAnterior == NULL)
        {
          grafoAux->meios = meioAtual->seguinte;
        }
        else
        {
          meioAnterior->seguinte = meioAtual->seguinte;
        }
        free(meioAtual);
        break;
      }

      meioAnterior = meioAtual;
      meioAtual = meioAtual->seguinte;
    }

    grafoAux = grafoAux->seguinte;
  }
  free(grafoAux);
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

// Recolher todos os meios
void recolherMeios(Meio *meios, Grafo *grafo)
{

  // TODO - Recolher todos os meios de todos os vértices do grafo
  // Array de strings trajeto
  char trajeto[100][100];
  // Array de inteiros para guardar o peso de cada meio
  int pesos[100];
  // Array de inteiros para guardar a distância entre cada vértice
  int distancias[100];

  // Peso dos tipos de meios
  int trotineta = 10, bicicleta = 20, carro = 200, barco = 500, aviao = 1000;
  // Tamanho dos arrays
  int trajetoLength = sizeof(trajeto) / sizeof(trajeto[0]);
  int pesosLength = sizeof(pesos) / sizeof(pesos[0]);
  int distanciasLength = sizeof(distancias) / sizeof(distancias[0]);

  Meio *meiosAux = meios;
  Grafo *grafoAux = grafo;
  while (grafoAux != NULL)
  {
    while (grafoAux->meios != NULL)
    {
      // Comparar o codigo do meio com o codigo do grafo
      if (meiosAux->codigo == grafoAux->meios->codigo)
      {
        // Verificar se está alugado ou não
        if (meiosAux->id_cliente == 0)
        {
          // Verificar a bateria
          if (meiosAux->bateria < 50)
          {
            // Adicionar vertice ao array de trajeto
            strcpy(trajeto[trajetoLength], grafoAux->vertice);
            // Adicionar peso ao array de pesos
            if (strcmp(meiosAux->tipo, "trotineta") == 0)
            {
              pesos[trajetoLength] = trotineta;
            }
            else if (strcmp(meiosAux->tipo, "bicicleta") == 0)
            {
              pesos[trajetoLength] = bicicleta;
            }
            else if (strcmp(meiosAux->tipo, "carro") == 0)
            {
              pesos[trajetoLength] = carro;
            }
            else if (strcmp(meiosAux->tipo, "barco") == 0)
            {
              pesos[trajetoLength] = barco;
            }
            else if (strcmp(meiosAux->tipo, "aviao") == 0)
            {
              pesos[trajetoLength] = aviao;
            }
            // Adicionar distância ao array de distâncias através da adjacência do vértice
            distancias[trajetoLength] = grafoAux->adjacentes->peso;
          }
        }
      }
      grafoAux->meios = grafoAux->meios->seguinte;
    }
    grafoAux = grafoAux->seguinte;
  }

  // Imprimir o trajeto
  int distanciaTotal = 0, pesoTotal = 0;
  printf("\nTrajeto a percorrer:\n");
  for (size_t i = 0; i < trajetoLength; i++)
  {
    printf("%s\n", trajeto[i]);
    distanciaTotal += distancias[i];
    pesoTotal += pesos[i];
  }
  printf("\nDistância total: %d\n", distanciaTotal);
  printf("Peso total: %d\n", pesoTotal);
  printf("\nMeios recolhido com sucesso!\n");
}