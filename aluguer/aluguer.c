#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "aluguer.h"

// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve o código do último registo + 1 (ou seja, o próximo a ser registado) se existir ou 0 caso contrário
int existeAluguer(Aluguer *inicio, int id_aluguer)
{
    while (inicio != NULL)
    {
        if (inicio->id_aluguer == id_aluguer)
            return (inicio->id_aluguer + 1);
        inicio = inicio->seguinte;
    }
    return (0);
}

// Criar uma nova Aluguer
void inserirAluguer(Aluguer *inicio, int id_meio, int id_cliente, float tempo)
{
    int cod = inicio->id_aluguer;
    while (1)
    {
        if (!existeAluguer(inicio, cod))
        {
            Aluguer *novo = malloc(sizeof(struct alugueres));
            if (novo != NULL)
            {
                novo->id_aluguer = cod;
                novo->id_cliente = id_cliente;
                novo->id_meio = id_meio;
                novo->tempo = tempo;
                novo->seguinte = inicio;
                FILE *fp;
                fp = fopen("./storage/alugueres.txt", "a");
                if (fp != NULL)
                {
                    Aluguer *aux = novo;
                    if (aux != NULL)
                    {
                        fprintf(fp, "%d;%d;%d;%f\n", aux->id_aluguer, aux->id_meio, aux->id_cliente, aux->tempo);
                    }
                    fclose(fp);
                    printf("Guardado no ficheiro com sucesso!\n");
                }
                else
                    printf("O ficheiro aluguers.txt não existe!\n");
                printf("Aluguer criado com sucesso!\n");
            }
            else
            {
                printf("Não foi possível alocar memória\npara criação de um novo aluguer!\n");
            }
            break;
        }
        else
            cod++;
    }
}

// inserir Aluguer no ficheiro
Aluguer *inserirAluguerFile(Aluguer *inicio, int id_aluguer, int id_meio, int id_cliente, float tempo)
{
    if (!existeAluguer(inicio, id_aluguer))
    {
        Aluguer *novo = malloc(sizeof(struct alugueres));
        if (novo != NULL)
        {
            novo->id_aluguer = id_aluguer;
            novo->id_cliente = id_cliente;
            novo->id_meio = id_meio;
            novo->tempo = tempo;
            novo->seguinte = inicio;
            return (novo);
        }
        else
        {
            return (inicio);
        }
    }
    else
        return (inicio);
}

// ler Alugueres
Aluguer *lerAluguer()
{
    FILE *fp;
    int id_aluguer, id_meio, id_cliente;
    float tempo;
    Aluguer *aux = NULL;
    fp = fopen("./storage/alugueres.txt", "r");
    if (fp != NULL)
    {
        Aluguer *novo = malloc(sizeof(fp));
        if (novo != NULL)
        {
            printf("Alugueres disponíveis:\n");
            while (!feof(fp))
            {
                fscanf(fp, "%d;%d;%d;%f \n", &id_aluguer, &id_meio, &id_cliente, &tempo);
                aux = inserirAluguerFile(aux, id_aluguer, id_meio, id_cliente, tempo);
                novo = aux;
                printf("%d %d %d %.2f\n", aux->id_aluguer, aux->id_meio, aux->id_cliente, aux->tempo);
            }
            fclose(fp);
        }
    }
    return (aux);
}