#include "include/acionador.h"

/*
	oo---5V
	oo
	oo---GND
	oo---TX
	oo---RX
	ooPWM(DNC)
	oo
	oo
	oo
TRG	oo
DIR0oo ECH1
DIR1oo ECH2
	oo ECH3
PWM on audio jack output.
*/

void init_acionador(){
/* //Utilizar primeiro init_sensores();
	if(getuid()!=0) {
		printf("Erro: deve ser root.\n");
		return 1;
	}
	if(wiringPiSetupGpio()==-1){
		printf("Erro na inicializacao da biblioteca wiringPi.\n");
		return 1;
	}
	*/

    delay(100);
	pinMode(DIR0,OUTPUT);
	delay(1);
	pinMode(DIR1,OUTPUT);
	delay(1);
	pwmSetMode(PWM_MODE_MS); //MS 32/50 = 12k || 32/100 = 6k || 32/200 = 3k
	pwmSetRange(PWM_RANGE);
	pwmSetClock(100);

}
	//printf("GPIO 9/11 = DIR/ESQ \n GPIO 10 = TRG \n GPIO 7/8/25 = ECH\n");

	//printf("Insira a string no formato:\n FRENTE0 VEL0 FRENTE1 VEL1 (ex: 1 31 1 31 = velocidade máxima para frente)\n");
int aciona_motores(int frente0, int vel0, int frente1, int vel1){
	if((frente0>1)||(frente1>1)||(vel0 >(PWM_RANGE))||(vel1 > (PWM_RANGE)))
	{
		return(-1);
	}
	digitalWrite(DIR0,frente0);
	digitalWrite(DIR1,frente1);
	pwmWrite(PWM0_OUT, vel0);
	pwmWrite(PWM1_OUT, vel1);
	return(0);//ok
}


void movimenta_robo(int classe){
    switch(classe){
        case 0:{
            aciona_motores(0,0,1,DEFAULT_VEL);
            break;
        }
        case 1:{
            aciona_motores(1,DEFAULT_VEL,1,DEFAULT_VEL);
            break;
        }
        case 2:{
            aciona_motores(1,DEFAULT_VEL,0,0);
            break;
        }
    }
}

void para_robo(){
    aciona_motores(0,0,0,0);
}

void reposiciona(){
    aciona_motores(1,DEFAULT_VEL,0,DEFAULT_VEL);
    delay(1000);
    return;
}
