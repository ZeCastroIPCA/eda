#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handleLogin.h"
#include "../contas/registo.h"
#include "../menus/menus.h"

// Verificar se o email e a password estão corretos e se o utilizador é um cliente ou gestor
Conta *handleLogin(Conta *contas)
{
    Conta *conta = NULL;
    char email[50], password[50];
    do
    {   
        getchar();
        printf("Email:");
        scanf("%[^\n]s", email);
        getchar();
        printf("Password:");
        scanf("%[^\n]s", password);
        conta = login(contas, email, password);
        if (conta == 0)
        {
            printf("\nO login falhou!\nTente outra vez.\n");
        }
    } while (conta == 0);
    printf("\nLogin efetuado com sucesso!\n");

    if (strcmp(conta->tipo, "cliente") == 0)
    {
        contas = menuCliente(contas, conta);
    }
    else if (strcmp(conta->tipo, "gestor") == 0)
    {
        menuGestorPrincipal(contas);
    }
    return (contas);
}

// Criar uma nova conta cliente
Conta *handleRegisto(Conta *contas)
{
    char email[50], password[50], nome[50], morada[50], nif[9];
    printf("Email: ");
    scanf("%s", email);
    printf("Password: ");
    scanf("%s", password);
    getchar();
    printf("Nome: ");
    scanf("%[^\n]s", nome);
    getchar();
    printf("Morada: ");
    scanf("%[^\n]s", morada);
    printf("NIF: ");
    scanf("%s", nif);
    contas = inserirConta(contas, email, password, nome, morada, nif);
}