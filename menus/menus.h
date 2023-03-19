#pragma once
#include <stdio.h>
#include "../contas/conta/conta.h"
#include "../meios/meio.h"

void menuGestorClientes(Conta *contas);
void menuGestorGestores();
void menuGestorMeios();
void menuGestorPrincipal(Conta *conta, Meio *meios);
Conta *menuPrincipal(Conta *conta, Meio *meios);
void menuCliente(Conta *contas, Conta *conta, Meio *meios);