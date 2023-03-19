#pragma once
#include <stdio.h>
#include "../conta/conta.h"
#include "../../meios/meio.h"

void handleLogin(Conta *contas, Meio *meios);
Conta *handleRegisto(Conta *contas);

Conta *login(Conta *inicio, char email[], char pass[]);
Conta *registo(Conta *inicio, char email[], char pass[], char nome[], char morada[], char nif[]);