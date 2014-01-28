#include "include/rede.h"

//Aleatorizar níveis considerados na ligação
void random_threshold(){
    unsigned char i, j, k, ja_sorteou;
    srand(time(NULL));
    for(i=0;i<NUMNEU;i++){
        for(j=0;j<NSENSORES;j++){
            do{
                niveis[i][j] = rand()%4;
                ja_sorteou = 0;
                for(k = 0;k < i; k++){
                    if(niveis[i][j] == niveis[k][j]){
                        ja_sorteou = 1;
                        break;
                    }
                }
            }while(ja_sorteou);
        }
    }
}

//Função para realizar a ligação entre cada neuronio e os sensores
unsigned char calc_endereco(int* entrada, int neu){
    unsigned char addr = 0;
    //Compara a entrada do sensor com o nível limite para aquele neuronio
    if(entrada[0] <= niveis[neu][0]) addr = 1; //001
    if(entrada[1] <= niveis[neu][1]) addr += 2;//010
    if(entrada[2] <= niveis[neu][2]) addr += 4;//100
    return(addr);
}

//Impressão para Debug
void print_threshold(){
    unsigned char i, j;
    srand(time(NULL));
    printf("S1| S2| S3 \n");
    for(i=0;i<NUMNEU;i++){
        for(j=0;j<NSENSORES;j++){
            printf("%d, ",niveis[i][j]);
        }
        printf("\n");
    }
}


void init_neuronios(int ind_atual){
    int cl, neu, i;
    for(cl=0;cl<NUMCLASS;cl++){ // zera cada classe
        for (neu=0;neu<NUMNEU;neu++){ // zera cada neuronio
            for (i=0;i<SIZENEU;i++){ //zera cada entrada
                    rede[cl][neu][i][ind_atual] = 0;
            }
        }
    }
}

void treinar_predef(int individuo_atual){
    int i, neu;
    for (i = 0; i<NENTRADAS; i++){
        for (neu = 0; neu<NUMNEU; neu++){
            //Define 1 na classe conhecida para essa conexão.
            rede[saida[i]][neu][calc_endereco((int *)entrada_predef[i],neu)][individuo_atual] = 1;
        }
    }
}

void print_rede(int individuo_atual){
    int cl, neu;
    for (cl=0;cl<NUMCLASS;cl++){
        printf("{\n");
        for (neu=0;neu<NUMNEU;neu++){
            //printf("%d: rede[0]=%d rede[1]=%d rede[2]=%d rede[3]=%d \n", cl,rede[cl][neu][0][individuo_atual],rede[cl][neu][1][individuo_atual],rede[cl][neu][2][individuo_atual],rede[cl][neu][3][individuo_atual]);
            printf("{%d,%d,%d,%d},\n",rede[cl][neu][0][individuo_atual],rede[cl][neu][1][individuo_atual],rede[cl][neu][2][individuo_atual],rede[cl][neu][3][individuo_atual]);
        }
        printf("}\n");

    }
}

int escolhe_classe(int * entrada, int individuo_atual){
    int maior_soma = 0, cl, neu;
    int cl_escolhida;
    int soma_cl[NUMCLASS];
    for(cl = 0; cl<NUMCLASS; cl++){
        soma_cl[cl] = 0;
        for (neu = 0; neu<NUMNEU; neu++){
            soma_cl[cl] += rede[cl][neu][calc_endereco(entrada,neu)][individuo_atual];
        }
        if(soma_cl[cl]>maior_soma)
        {
                maior_soma = soma_cl[cl];
                cl_escolhida = cl;
        }
    }
    //printf("%d",maior_soma);
    return(cl_escolhida);
}

int escolhe_classe_predef(int * entrada){
    int maior_soma = 0, cl = 0, neu = 0;
    int cl_escolhida = 0;
    int soma_cl[NUMCLASS];
    for(cl = 0; cl<NUMCLASS; cl++){
        soma_cl[cl] = 0;
        for (neu = 0; neu<NUMNEU; neu++){
            soma_cl[cl] += rede_predef[cl][neu][calc_endereco(entrada,neu)];
        }
        if(soma_cl[cl]>maior_soma)
        {
            maior_soma = soma_cl[cl];
            cl_escolhida = cl;
        }
    }
    //printf("%d",maior_soma);
    return(cl_escolhida);
}
