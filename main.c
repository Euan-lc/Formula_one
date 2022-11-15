#include "libs/f1.h"
static int carIds[] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22,
                       5, 18, 6, 23, 77, 24, 47, 9};

void main(int argc, char *argv[]) {
    int shmid, cpid, num_cars, shmkey = 420;

    //generate seed for rand
    srand48(time(0));

    //display
    initscr();
    start_color();
    init_pair(1,COLOR_MAGENTA, COLOR_BLACK);
    num_cars = atoi(argv[1]);

    //shared memory
    shmid = shmget(shmkey, num_cars * sizeof(car), IPC_CREAT | 0666);
    car circuit[] = shmat(shmid, 0, 0);

    printf("%d\n",num_cars);

    for (int i = 0; i < num_cars; i++) {
        init_car(&circuit[i], carIds[i]);
    }

    for (int i = 0; i < num_cars; i++) {
        if (fork() == 0) {
            car child;
            child = circuit[i];
            printf("[son] pid %d from [parent] pid %d and car id is %d\n", getpid(), getppid(), child.id);
            lap_car(&child);
            printf("car %d has a lap time of %g\n", child.id, child.total_time);
            exit(0);
        }else{
            halfdelay(5);
            for(int i = 0; i < 50; i++) {
                car buffer[] = malloc(num_cars * sizeof(car));
                memcpy(buffer,circuit,num_cars sizeof(car));
                bubble_sort(buffer, NUM_CARS);
                //best_sector(circuit, NUM_CARS);

                display_scores(buffer, NUM_CARS);

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