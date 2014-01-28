#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include "include/defines.h"
#include "rede.c"
#include "sensores.c"
#include "supervisor.c"
#include "evolutivo.c"
#include "acionador.c"

void control_event(int sig);

FILE *arq;

int main (void)
{
    (void)signal (SIGINT,control_event);
    (void)signal (SIGQUIT,control_event);

    struct timeval inicio, atual;
    int i,a[3], k, classe;
    piHiPri(99);
    arq = fopen("evolucao.csv", "w");

    int niveis2[4][3] =
    {
        {3, 0, 1},
        {1, 2, 3},
        {2, 1, 2},
        {0, 3, 0}
    };
    int j;
    for(i=0; i<NUMNEU; i++)
        for(j=0; j<NSENSORES; j++)
            niveis[i][j] = niveis2[i][j];

    init_sonar();

    init_acionador();

    init_neuronios(0); //Zerar neuronios

    treinar_predef(0); //Treina baseado na info. do especialista

    print_rede(0);
    i=0;
    while(1)
    {
        gettimeofday(&inicio, NULL);
        fitness[i] = 0;
        do
        {
            ler_niveis(a);
            printf("%d | %d | %d\n", a[0], a[1], a[2]);
            classe = escolhe_classe(a,0);
		printf("%d", classe);
            //Movimentar robo na direção da classe escolhida
            movimenta_robo(classe);
            delay(50);
            if(colidiu(a))  //REDE NEURAL || SUPERVISOR
            {
                delay(10);
                ler_niveis(a); //Le novamente
                if(colidiu(a))
                {
	            delay(10);
                    ler_niveis(a); //Le novamente
        	    if(colidiu(a))
	            {
                    	fitness[i] -= 10;
                    	reposiciona();
		    }
                }
            }
            else
            {
                fitness[i] += 1;
                if(classe == 1) fitness[i]++;
            }
            gettimeofday(&atual, NULL);
        }
        while(atual.tv_sec - inicio.tv_sec < 30); // 30 segundos //TESTAR TEMPO || TROCAR IND
        fprintf(arq,"%d\n",fitness[0]);
    }
    return(0);
}

void control_event(int sig)
{
    printf("\nExiting...\n");
    para_robo();
    fclose(arq);
    delay(100); //wait a little for the pwm to finish write
    exit(0);
}
