#ifndef ACIONADOR_H_INCLUDED
#define ACIONADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "defines.h"


void init_acionador();
int aciona_motores(int frente0, int vel0, int frente1, int vel1);
void reposiciona();
void para_robo();

#endif // ACIONADOR_H_INCLUDED
