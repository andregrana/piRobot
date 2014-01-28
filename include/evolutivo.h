#ifndef EVOLUTIVO_H_INCLUDED
#define EVOLUTIVO_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "defines.h"


int fitness[SIZEPOP];
int TAXA_MUTACAO;

//HEADERS

void init_pop(int rede[][NUMNEU][SIZENEU][SIZEPOP]);
void selecao();
void crossover(int rede[][NUMNEU][SIZENEU][SIZEPOP]);
void mutacao(int rede[][NUMNEU][SIZENEU][SIZEPOP]);

void ajustar_mutacao();

void print_inline(int rede[][NUMNEU][SIZENEU][SIZEPOP], int individuo);
#endif // EVOLUTIVO_H_INCLUDED
