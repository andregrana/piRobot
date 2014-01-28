#ifndef REDE_H_INCLUDED
#define REDE_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "defines.h"

int rede[NUMCLASS][NUMNEU][SIZENEU][SIZEPOP];
int niveis[NUMNEU][NSENSORES];


/**Informações do "especialista" para treino*********************/
#define NENTRADAS 11

const int entrada_completa[64][3]=
{    {0,0,0},    {0,0,1},    {0,0,2},    {0,0,3},
    {0,1,0},    {0,1,1},    {0,1,2},    {0,1,3},
    {0,2,0},    {0,2,1},    {0,2,2},    {0,2,3},
    {0,3,0},    {0,3,1},    {0,3,2},    {0,3,3},
    {1,0,0},    {1,0,1},    {1,0,2},    {1,0,3},
    {1,1,0},    {1,1,1},    {1,1,2},    {1,1,3},
    {1,2,0},    {1,2,1},    {1,2,2},    {1,2,3},
    {1,3,0},    {1,3,1},    {1,3,2},    {1,3,3},
    {2,0,0},    {2,0,1},    {2,0,2},    {2,0,3},
    {2,1,0},    {2,1,1},    {2,1,2},    {2,1,3},
    {2,2,0},    {2,2,1},    {2,2,2},    {2,2,3},
    {2,3,0},    {2,3,1},    {2,3,2},    {2,3,3},
    {3,0,0},    {3,0,1},    {3,0,2},    {3,0,3},
    {3,1,0},    {3,1,1},    {3,1,2},    {3,1,3},
    {3,2,0},    {3,2,1},    {3,2,2},    {3,2,3},
    {3,3,0},    {3,3,1},    {3,3,2},    {3,3,3}
};

const int saida_completa[64] = {0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,2,2,2,0,0,0,2,0,0,0,0,
0,0,0,0,0,1,1,1,0,0,0,2,0,0,0,0,0,0,0,0,0,1,1,1};

const int entrada_predef[NENTRADAS][NSENSORES]={ //**inventada
    {0,0,0}, //D
    {0,0,3}, //D
    {0,3,0}, //F
    {3,0,0}, //E
    {1,2,3}, //D
    {3,2,1}, //E
    {1,3,1}, //F
    {3,1,3}, //D
    {3,1,1}, //E
    {3,3,2}, //F
    {2,3,3} //F
};
const int saida[NENTRADAS] = {2, 2, 1, 0, 2, 0, 1, 2, 0, 1, 1};

const int rede_predef[NUMCLASS][NUMNEU][SIZENEU] =
        {
            {
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,1}
            },
            {
                {0,0,0,0},
                {1,0,0,0},
                {1,0,0,0},
                {0,0,0,1}
            },
            {
                {0,0,0,0},
                {0,0,1,1},
                {1,1,0,1},
                {0,0,0,1}
            }
        };



/*****************************************************************/



unsigned char calc_endereco(int* entrada, int neu);
void print_threshold();
void treinar_predef(int individuo_atual);
void print_rede(int individuo_atual);
void random_threshold();
void init_neuronios(int individuo_atual);
int escolhe_classe(int * entrada, int individuo_atual);

#endif // REDE_H_INCLUDED
