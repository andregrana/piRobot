#ifndef SENSORES_H_INCLUDED
#define SENSORES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
#include <sys/time.h>
#include "defines.h"

/*
        ...
        | | | GPIO 23
        | | | GPIO 24
GPIO 10 |V|-| DNC
GPIO 9	|A|A| GPIO 25
GPIO 11	|C|M| GPIO 8
    DNC	|-|R| GPIO 7
	 - -
*/


//Definicao dos pinos utilizados pelos sensores (sonares)

int waitState(unsigned char Pin, unsigned char State);
double read_sensor(unsigned char i);
void init_sonar();
void ler_niveis (int a[]);
void ler_niveis_mediana(int a[]);

#endif // SENSORES_H_INCLUDED
