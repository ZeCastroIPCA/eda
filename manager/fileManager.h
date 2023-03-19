#pragma once
#include <stdio.h>
#include "../contas/conta/conta.h"


Conta *inserirContaFile(Conta *inicio, int cod, char tipo[], char email[], char pass[], char nome[], char morada[], char nif[], float saldo, int meio_id);

int saveContasBin(Conta *inicio);