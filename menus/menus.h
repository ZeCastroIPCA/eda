#pragma once
#include <stdio.h>
#include "../contas/conta/conta.h"
#include "../meios/meio.h"

void menuGestorContas(Conta *contas);
void menuGestorMeios();
void menuGestorPrincipal(Conta *conta, Meio *meios);
void menuPrincipal(Conta *conta, Meio *meios);
void menuCliente(Conta *contas, Conta *conta, Meio *meios);