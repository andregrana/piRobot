#include "include/sensores.h"

int waitState(unsigned char Pin, unsigned char State)
{
	struct timeval now, start;
	long micros;
	gettimeofday(&start, NULL);
	micros = 0;
	while(digitalRead(Pin) != State){
		gettimeofday(&now, NULL);
		micros = now.tv_usec - start.tv_usec;
		if(micros < 0) micros = 1000000L + now.tv_usec;
		if(micros > TIMEOUT) return(0);
	}
	return micros;
}

double read_sensor(unsigned char i){
    double dist = 0;
    int echo_atual = ECHO_PIN1;
    switch(i){
        case 1:{
            echo_atual = ECHO_PIN2;
            break;
        }
        case 2:{
            echo_atual = ECHO_PIN3;
            break;
        }
    }
    delay(60);
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(20);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIGGER_PIN, LOW);
    waitState(echo_atual,HIGH);

    dist = waitState(echo_atual, LOW) * 0.017;
    return(dist); //centimetros de distancia
}


void init_sonar(){
    if(getuid()!=0) {
		printf("Erro: deve ser root.\n");
		exit(0);
	}
	if(wiringPiSetupGpio()==-1){
		printf("Erro na inicializacao da biblioteca wiringPi.\n");
		exit(0);
	}
    piHiPri(99);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN1, INPUT);
    pinMode(ECHO_PIN2, INPUT);
    pinMode(ECHO_PIN3, INPUT);
}

void ler_niveis (int a[]){
    int i;
    double dist =0;
    for(i=0;i<NSENSORES;i++){
        dist = read_sensor(i);

        if ((dist >= LIMIAR3) || (dist == 0))
            a[i] = 3;
        else if (dist >= LIMIAR2 && dist < LIMIAR3)
            a[i] = 2;
        else if (dist >= LIMIAR1 && dist < LIMIAR2)
            a[i] = 1;
        else if (dist >= LIMIAR0 && dist < LIMIAR1)
            a[i] = 0;
        else{
            a[i] = -1;
		printf("%f",dist);
	}
    }
    return;
}

void ler_niveis_mediana(int a[]){
    int i, meio;
    double vet_mediana[3];
    double dist =0;
    for(i=0;i<NSENSORES;i++){
        //le distancia 3 vezes
        vet_mediana[0] = read_sensor(i);
        vet_mediana[1] = read_sensor(i);
        vet_mediana[2] = read_sensor(i);
        meio = 2;
        if(((vet_mediana[0]>vet_mediana[1])&&(vet_mediana[1]>vet_mediana[2]))||((vet_mediana[2]>vet_mediana[1])&&(vet_mediana[1]>vet_mediana[0])))
            meio = 1;
        if(((vet_mediana[0]>vet_mediana[1])&&(vet_mediana[2]>vet_mediana[0]))||((vet_mediana[0]>vet_mediana[2])&&(vet_mediana[1]>vet_mediana[0])))
            meio = 0;


        //utiliza o valor intermediario
        dist = vet_mediana[meio];
        if ((dist >= LIMIAR3) || (dist <= 0))
            a[i] = 3;
        else if (dist >= LIMIAR2 && dist < LIMIAR3)
            a[i] = 2;
        else if (dist >= LIMIAR1 && dist < LIMIAR2)
            a[i] = 1;
        else if (dist >= LIMIAR0 && dist < LIMIAR1)
            a[i] = 0;
        else{
            a[i] = -1;
		printf("%f",dist);
}
    }
    return;

}
