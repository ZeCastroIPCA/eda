#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
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
      //printf("\nMeios disponíveis:\n");
      while (!feof(fp))
      {
        fscanf(fp, "%d;%[^;];%f;%f;%d;%f;%ld\n", &cod, tipo, &bat, &aut, &id_cliente, &custo, &inicio_aluguer);
        aux = inserirMeioFile(aux, cod, tipo, bat, aut, id_cliente, custo, inicio_aluguer);
        novo = aux;
        //printf("%d %s %.2f %.2f %d %.2f %ld\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia, aux->id_cliente, aux->custo, aux->inicio_aluguer);
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
    Meio *meio = *meios;
    novo_meio->seguinte = meio;
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

  // Update the meios list in the grafo
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

// Recolher todos os meios | Tentativa 1 (não funciona corretamente)
// void recolherMeios(Meio *meios, Grafo *grafo)
// {
// // Definir a capacidade máxima do camião
// #define CAPACIDADE_CAMIAO 10000

//   // Array de strings trajeto
//   char trajeto[100][100];
//   // Array de inteiros para guardar o peso de cada meio
//   int pesos[100];
//   // Array de inteiros para guardar a distância entre cada vértice
//   int distancias[100];

//   // Peso dos tipos de meios
//   int trotineta = 10, bicicleta = 20, carro = 200, barco = 500, aviao = 1000;
//   // Tamanho dos arrays
//   int trajetoLength = 0;

//   Grafo *grafoAux = grafo;

//   // Percorrer todos os vértices do grafo
//   while (grafoAux != NULL)
//   {
//     Meio *meiosAux = grafoAux->meios;
//     printf("Grafo:%s\n", grafoAux->vertice);
//     // Percorrer todos os meios do vértice atual
//     while (meiosAux != NULL)
//     {
//       Meio *meio = meios;
//       printf("Meios Grafo:%d %s %.0f\n", meiosAux->codigo, meiosAux->tipo, meiosAux->bateria);
//       while (meio != NULL)
//       {
//         printf("Meios:%d %s %.0f\n", meio->codigo, meio->tipo, meio->bateria);
//         if (meio->codigo == meiosAux->codigo)
//         {
//           // Verificar se está alugado ou não
//           if (meiosAux->id_cliente == 0)
//           {
//             // Verificar a bateria
//             if (meiosAux->bateria < 50)
//             {
//               // Adicionar vértice ao array de trajeto
//               strcpy(trajeto[trajetoLength], grafoAux->vertice);
//               // Adicionar peso ao array de pesos
//               if (strcmp(meiosAux->tipo, "trotineta") == 0)
//               {
//                 pesos[trajetoLength] = trotineta;
//               }
//               else if (strcmp(meiosAux->tipo, "bicicleta") == 0)
//               {
//                 pesos[trajetoLength] = bicicleta;
//               }
//               else if (strcmp(meiosAux->tipo, "carro") == 0)
//               {
//                 pesos[trajetoLength] = carro;
//               }
//               else if (strcmp(meiosAux->tipo, "barco") == 0)
//               {
//                 pesos[trajetoLength] = barco;
//               }
//               else if (strcmp(meiosAux->tipo, "aviao") == 0)
//               {
//                 pesos[trajetoLength] = aviao;
//               }
//               // Adicionar distância ao array de distâncias através da adjacência do vértice
//               distancias[trajetoLength] = grafoAux->adjacentes->peso;

//               // Incrementar o contador de tamanho do array
//               trajetoLength++;
//             }
//           }
//           break;
//         }
//         meio = meio->seguinte;
//       }

//       meiosAux = meiosAux->seguinte;
//     }
//     grafoAux = grafoAux->seguinte;
//   }

//   // Algoritmo Vizinho mais Próximo
//   char trajetoFinal[100][100];
//   int pesosFinal[100];
//   int distanciasFinal[100];
//   int trajetoFinalLength = 0;

//   int visitado[100] = {0};
//   int posAtual = 0;
//   visitado[posAtual] = 1;
//   int capacidadeAtual = 0;

//   for (int i = 0; i < trajetoLength; i++)
//   {
//     int proximoVertice = -1;
//     int menorDistancia = INT_MAX;

//     // Procurar o vértice não visitado mais próximo
//     for (int j = 0; j < trajetoLength; j++)
//     {
//       if (!visitado[j])
//       {
//         if (proximoVertice == -1 || distancias[j] < menorDistancia)
//         {
//           proximoVertice = j;
//           menorDistancia = distancias[j];
//         }
//       }
//     }

//     // Verificar se o camião tem capacidade para transportar o meio de mobilidade
//     if (capacidadeAtual + pesos[proximoVertice] <= CAPACIDADE_CAMIAO)
//     {
//       // Adicionar vértice, peso e distância ao trajeto final
//       strcpy(trajetoFinal[trajetoFinalLength], trajeto[proximoVertice]);
//       pesosFinal[trajetoFinalLength] = pesos[proximoVertice];
//       distanciasFinal[trajetoFinalLength] = distancias[proximoVertice];
//       trajetoFinalLength++;

//       // Marcar o vértice como visitado
//       visitado[proximoVertice] = 1;

//       // Atualizar a posição atual
//       posAtual = proximoVertice;

//       // Atualizar a capacidade atual do camião
//       capacidadeAtual += pesos[proximoVertice];
//     }
//   }

//   // Imprimir o trajeto final
//   int distanciaTotal = 0, pesoTotal = 0;
//   printf("\nTrajeto a percorrer:\n");
//   for (int i = 0; i < trajetoFinalLength; i++)
//   {
//     if (i != 0)
//     {
//       printf("->");
//     }
//     printf("%s", trajetoFinal[i]);
//     printf("\nDistância: %d\n", distanciasFinal[i]);
//     printf("\nPeso: %d\n", pesosFinal[i]);
//     distanciaTotal += distanciasFinal[i];
//     pesoTotal += pesosFinal[i];
//   }
//   printf("->%s\n", trajetoFinal[0]);
//   printf("\nDistância total: %d\n", distanciaTotal);
//   printf("Peso total: %d\n", pesoTotal);
//   printf("\nMeios recolhidos com sucesso!\n");
// }

// Tentativa 2 | (não funciona, faz apenas um vértice)
void recolherMeios(Meio *meios, Grafo *grafo)
{
  // capacidade do camião
  int capacidade = 100;

  int count = 1;
  int recolhidos = 0;
  Grafo *vAtual = grafo;
  Grafo *vPrimeiro = grafo;

  // Encontrar o último vértice do grafo
  Grafo *vAux = grafo;
  Grafo *vUltimo = NULL;
  while (vAux != NULL)
  {
    vUltimo = vAux;
    vAux = vAux->seguinte;
  }
  printf("----  Percurso de recolha  ----\n");
  printf("---------------------------------------------------\n");
  printf("| Volta | ID | Bateria | Geocódigo                |\n");
  printf("---------------------------------------------------\n");
  while (vAtual != vUltimo)
  {
    //printf("Atual: %s\n", vAtual->vertice);
    if (!vAtual->visitado)
    {
      Meio *vAtualMeios = vAtual->meios;
      while (vAtualMeios != NULL)
      {
        //printf("Meio Grafo: %d %s\n", vAtualMeios->codigo, vAtualMeios->tipo);
        Meio *meiosAux = meios;
        while (meiosAux != NULL && recolhidos < capacidade)
        {
          //printf("Meio Meio: %d %s\n", meiosAux->codigo, meiosAux->tipo);
          // Verificar se o meio está alugado
          if (meiosAux->id_cliente == 0)
          {
            // Verificar se o meio está na mesma localização que o vértice atual (através do código) e se a bateria está abaixo de 50%
            if (meiosAux->bateria < 50 && meiosAux->codigo == vAtualMeios->codigo)
            {
              recolhidos++;
              printf("| %-5d | %-2d | %.2f%% | %-25s |\n", count, meiosAux->codigo, meiosAux->bateria, vAtual->vertice);
              printf("---------------------------------------------------\n");
              meiosAux->bateria = 100;
              break;
            }
          }

          meiosAux = meiosAux->seguinte;
        }

        // Verificar se o camião está cheio
        if (recolhidos == capacidade)
        {
          count++;
          recolhidos = 0;
          vAtual = vPrimeiro;

          // Trocar a variável visitado para 0 em todos os vertices
          Grafo *limparAux = grafo;
          while (limparAux != NULL)
          {
            limparAux->visitado = 0;
            limparAux = limparAux->seguinte;
          }
          continue;
        }
        vAtual->visitado = 1;
        vAtualMeios = vAtualMeios->seguinte;
      }
    }

    Grafo *vSeguinte = NULL;
    Adjacente *adjacentesAux = vAtual->adjacentes;
    int minDistancia = INT_MAX;

    while (adjacentesAux != NULL)
    {
      // Verificar se o vértice adjacente já foi visitado e se a distância (peso) é menor que a distância mínima
      Grafo *grafoAdj = existeVerticeReturn(grafo, adjacentesAux->vertice);
      if (!grafoAdj->visitado && adjacentesAux->peso < minDistancia)
      {
        minDistancia = adjacentesAux->peso;
        vSeguinte = grafoAdj;
      }
      adjacentesAux = adjacentesAux->seguinte;
    }

    // O vértice seguinte passa a ser o vértice atual
    vAtual = vSeguinte;
  }

  // Trocar a variável visitado para 0 em todos os vertices
  Grafo *limparAux = grafo;
  while (limparAux != NULL)
  {
    limparAux->visitado = 0;
    limparAux = limparAux->seguinte;
  }
}
