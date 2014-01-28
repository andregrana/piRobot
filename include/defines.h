#ifndef DEFINES_H
#define DEFINES_H

//DEFINES AG --------------------------------
#define SIZEPOP 4
#define TAXA_CROSSOVER 100
//#define TAXA_MUTACAO 15


//DEFINES REDE NEURAL -----------------------------
#define NUMCLASS 3 // D E F
#define NUMNEU 4

// 3 Sensores e 4 Níveis =  4^3 = 64 possibilidades
// Aleatoriza o nível para cada sensor em cada neurônio
#define SIZENEU 8

//DEFINES SONARES ----------------------------------
#define NSENSORES 3

#define TIMEOUT	5000

#define LIMIAR0 14.0
#define LIMIAR1 24.0
#define LIMIAR2 34.0
#define LIMIAR3 44.0


#define TRIGGER_PIN 10
#define ECHO_PIN1 25
#define ECHO_PIN2 8
#define ECHO_PIN3 7


#define PWM1_OUT 40
#define PWM0_OUT 45
#define PWM_RANGE 32

#define DIR0 9
#define DIR1 11

#define DEFAULT_VEL 32


#endif //DEFINES_H
