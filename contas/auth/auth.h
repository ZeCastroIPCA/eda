#pragma once
#include <stdio.h>
#include "../conta/conta.h"
#include "../../meios/meio.h"

void handleLogin(Conta *contas, Meio *meios);
void handleRegisto(Conta *contas, int who);

Conta *login(Conta *contas, char email[], char pass[]);
void registo(Conta *contas, char email[], char pass[], char nome[], char morada[], char nif[], char tipo[]);