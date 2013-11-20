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
FILE *arq_rede;

int main (void)
{
    (void)signal (SIGINT,control_event);
    (void)signal (SIGQUIT,control_event);

    struct timeval inicio, atual;
    int i, j, k, a[3], classe;
    piHiPri(99);
    arq_rede = fopen("rede.dat","r");

/* Matriz de conexões fixada para continuar de rede salva */
    const int niveis2[4][3] =
    {
        {3, 0, 1},
        {1, 2, 3},
        {2, 1, 2},
        {0, 3, 0}
    };

    for(i=0; i<NUMNEU; i++)
    {
        for(j=0; j<NSENSORES; j++)
        {
            niveis[i][j] = (int) niveis2[i][j];
        }
    }

    init_sonar();
    init_acionador();

    //INICIALIZAÇÃO DA POP
    if(arq_rede == NULL)
    {
        //init_pop(rede);

        for(i=0;i<SIZEPOP;i++){
            init_neuronios(i); //Zerar neuronios
            treinar_predef(i); //Treina baseado na info. do especialista
        }
        melhor_atual = 0;
        mutacao(rede);
    }
    else
    {
        carregar_rede(rede, arq_rede);
        fclose(arq_rede);
    }
   	getchar();

    cont_sem_melhora = 0;
    TAXA_MUTACAO = 100;

    while(1)
    {
        //AVALIAÇÃO
        for(i = 0; i< SIZEPOP;)
        {
            gettimeofday(&inicio, NULL);
            fitness[i] = 0;
            do
            {
                ler_niveis(a);
                
                classe = escolhe_classe(a, i);
                //Movimentar robo na direção da classe escolhida
                movimenta_robo(classe);
                delay(50);
                
                if(colidiu(a))  // SUPERVISOR
                {
                    delay(10);
                    ler_niveis(a); //Le novamente
                    if(colidiu(a))
                    {
                        delay(10);
                        ler_niveis(a); //Le novamente
                        if(colidiu(a))
                        {
                            //Colisao
                            //tratamento colisao
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
            while(atual.tv_sec - inicio.tv_sec < 20); // 30 segundos //TESTAR TEMPO || TROCAR IND

            printf("\nFITNESS INDIVIDUO [%d] = %d ", i, fitness[i]);
            i++; //troca individuo
        }

        selecao();

        double media = 0;
        for(k=0; k<SIZEPOP; k++)
        {
            media += fitness[k];
        }
        media /= SIZEPOP;
	      
	      arq = fopen("evolucao.csv","a");
        fprintf(arq,"%d; %d\n",fitness[melhor_atual],(int)media);
	      fclose(arq);
        printf("\nMEDIA = %d\n", (int) media);

        arq_rede = fopen("rede.dat","w");
        salvar_rede(rede,arq_rede);
        fclose(arq_rede);

        crossover(rede);
        mutacao(rede);
        ajustar_mutacao();
    }
    return(0);
}

void control_event(int sig)
{
    printf("\nExiting...\n");
    para_robo();
    getchar();
    delay(100); //wait a little for the pwm to finish write
    exit(0);
}
