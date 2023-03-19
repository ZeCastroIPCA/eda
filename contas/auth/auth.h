#pragma once
#include <stdio.h>
#include "../conta/conta.h"

void handleLogin(Conta *contas);
void handleRegisto(Conta *contas);

Conta *login(Conta *inicio, char email[], char pass[]);
Conta *registo(Conta *inicio, char email[], char pass[], char nome[], char morada[], char nif[]);