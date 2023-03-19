#pragma once
#include <stdio.h>

int menuGestorClientes(Conta *contas);
int menuGestorGestores();
int menuGestorMeios();
int menuGestorPrincipal(Conta *conta);
Conta *menuPrincipal(Conta *conta);
Conta *menuCliente(Conta *contas, Conta *conta);