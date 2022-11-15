#include "libs/vroum.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

#define NUM_CARS 20

static int carIds[] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9};


int main(){
    car *circuit;
    car *test;
    int    shmId;
    srand48(time(0));

    shmId = shmget(69, sizeof(car) * 20, IPC_CREAT | 0666);
    circuit = (car *)shmat(shmId,0,0);
    test = &circuit[2];
    //init_car(&circuit[2],carIds[2]);
    //lap_car(&circuit[2]);

    for (int i = 0; i < NUM_CARS; i++){
        init_car(&circuit[i], carIds[i]);
    }
    lap_car(test);
    //race_cars(circuit, 5, 1);

    shmdt(circuit);
}