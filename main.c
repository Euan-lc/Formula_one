#include "libs/f1.h"

void main(int argc, char *argv[]) {
    int shmid, cpid, num_cars, shmkey = 420;

    //generate seed for rand
    srand48(time(0));
    num_cars = atoi(argv[1]);

    //display
    initscr();
    start_color();
    init_pair(1,COLOR_MAGENTA, COLOR_BLACK);


    //shared memory
    shmid = shmget(shmkey, num_cars * sizeof(car), IPC_CREAT | 0666);
    car *circuit = shmat(shmid, 0, 0);

    printf("%d\n",num_cars);

    for (int i = 0; i < num_cars; i++) {
        init_car(&circuit[i], carIds[i]);
    }

    for (int i = 0; i < num_cars; i++) {
        if (fork() == 0) {
            car child;
            child = circuit[i];
            //printf("[son] pid %d from [parent] pid %d and car id is %d\n", getpid(), getppid(), child.id);
            for(int i = 0; i < 50; i++){
                sleep(0.5);
                lap_car(&circuit[i]);
            }
            //printf("car %d has a lap time of %g\n", child.id, child.total_time);
            exit(0);
        }else{
            halfdelay(5);
            for(int i = 0; i < 10; i++) {
                car * buffer = malloc(num_cars * sizeof(car));
                memcpy(buffer,circuit,num_cars * sizeof(car));
                //bubble_sort(buffer, num_cars);

                display_scores(buffer, num_cars);

                getch();
                erase();
                refresh();
            }
        }
    }
    //shared memory
    shmctl(shmid, IPC_RMID, NULL);
    shmdt(circuit);

    //display
    getch();
    endwin();

    exit(0);
}