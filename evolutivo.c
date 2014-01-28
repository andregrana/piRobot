#include "include/evolutivo.h"

/*Variáveis para auxiliar no controle da taxa de mutação*/
int melhor_atual, melhor_anterior, cont_sem_melhora;

/*Inicializar aleatóriamente a população*/
void init_pop(int rede[][NUMNEU][SIZENEU][SIZEPOP]){
    int i,j,cl,neu;
    for(i = 0; i<SIZEPOP; i++){
        for(cl=0;cl<NUMCLASS;cl++){
            for (neu=0;neu<NUMNEU;neu++){
                for (j=0;j<SIZENEU;j++){
                        rede[cl][neu][j][i] = rand()%2;
}   }   }   }   }

/*Encontra-se nessa etapa o melhor indivíduo*/
void selecao(){
    int i;
    melhor_anterior = melhor_atual;
    for(i = 0; i < SIZEPOP; i++){
        if(fitness[i]>fitness[melhor_atual]){
            melhor_atual = i;
}   }   }

/*No crossover o melhor cruza com todos*/
void crossover(int rede[][NUMNEU][SIZENEU][SIZEPOP]){
    int i, cl, neu, j;
    for(i = 0; i < SIZEPOP; i++){
        if (i == melhor_atual) continue;
        for(cl=0;cl<NUMCLASS;cl++){
            for (neu=0;neu<NUMNEU;neu++){
                for (j=0;j<SIZENEU;j++){
                    /*50% para cada pai e possui uma taxa de sucesso (para cada bit)*/
                    if((rand()%2) && (rand()%100<TAXA_CROSSOVER)){
                        rede[cl][neu][j][i] = rede[cl][neu][j][melhor_atual];
}   }   }   }   }   }

/*A mutação faz com que um bit do indivíduo se invertido*/
void mutacao(int rede[][NUMNEU][SIZENEU][SIZEPOP]){
    int i, cl, neu, j;
    for(i = 0; i < SIZEPOP; i++){
        if (i == melhor_atual) continue;
        for(cl=0;cl<NUMCLASS;cl++){
            for (neu=0;neu<NUMNEU;neu++){
                for (j=0;j<SIZENEU;j++){
                    if(rand()%100<TAXA_MUTACAO){
                        rede[cl][neu][j][i] = !rede[cl][neu][j][i];
}   }   }   }   }   }

/*Diminui a mutação e aumenta, em ciclos.*/
void ajustar_mutacao(){
    if(melhor_atual == melhor_anterior){
        cont_sem_melhora++;
        if(cont_sem_melhora%5 == 0){
            if(TAXA_MUTACAO > 2)
                TAXA_MUTACAO *= 0.9;
        }
        if(cont_sem_melhora%140 == 0){
            TAXA_MUTACAO = 100;
        }
    }else{
        cont_sem_melhora = 0;
}   }


void print_inline(int rede[][NUMNEU][SIZENEU][SIZEPOP], int individuo){
    int neu, cl, pos;
    for(cl = 0; cl < NUMCLASS; cl++){
        for(neu = 0; neu < NUMNEU; neu++){
            for(pos = 0; pos < SIZENEU; pos++){
                printf("%d", rede[cl][neu][pos][individuo]);
    }   }   }
    printf("\n");
}
