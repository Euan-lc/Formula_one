#include "libs/f1.h"

//TODO: help message
//TODO: .csv creation
//TODO: check param validity

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
    // Print the help message
    printf("Usage: ./Formula_one [weekend] [race_type] [race_number] [num_turns/time]\n\n");

    printf("  -h     display this help message\n\n");

    printf("weekend is the name of the file which will store the race results\n\n");

    printf("race types :\n");
    printf("  -tryout\n");
    printf("  -qualifiers\n");
    printf("  -sprint\n");
    printf("  -final\n\n");
    printf("race_number :\n");
    printf("race_number is for tryout and qualifiers and is from 1 to 3\n\n");

    printf("num_turns :\n");
    printf("num_turns is for sprint or final and determines the number of turns the cars have to complete.\n");

    return 0;
    }
    
    int shmid, cpid, num_cars, shmkey = 420;
    char *race_name;

    //display
    initscr();
    start_color();
    init_pair(1,COLOR_MAGENTA, COLOR_BLACK);

    //shared memory
    shmid = shmget(shmkey, num_cars * sizeof(car), IPC_CREAT | 0666);
    car *circuit = shmat(shmid, 0, 0);

    if (argc == 4 && strcmp(argv[2], "-sprint") == 0) {
        if (strcmp(argv[3], "1") == 0){
            //create file
        }

        race_name = "p" + argv[3];
        for (int i = 0; i < num_cars; i++) init_car(&circuit[i], carIds[i]);

        //define condition for race finish
    }



    for (int i = 0; i < num_cars; i++) {
        if ((cpid = fork()) == 0) {
            car child;
            child = circuit[i];

            //generate seed for rand based on
            srand48(time(0) + child.id);

            //printf("[son] pid %d from [parent] pid %d and car id is %d\n", getpid(), getppid(), child.id);
            for(int j = 0; j < 20; j++){
                sleep(1);
                //circuit[i].s1 = j;
                lap_car(&circuit[i]);
            }
            //printf("car %d has a lap time of %g\n", child.id, child.total_time);
            exit(0);
        }
    }

    if(cpid != 0){
        halfdelay(5);
        for(int i = 0; i < 20; i++) {
            car * buffer = malloc(num_cars * sizeof(car));
            memcpy(buffer,circuit,num_cars * sizeof(car));
            bubble_sort(buffer, num_cars);
            printw("%d\n", i);
            display_scores(buffer, num_cars);

            getch();
            erase();
            refresh();
        }

        //shared memory
        shmctl(shmid, IPC_RMID, NULL);

        //display
        getch();
        endwin();
    }

    write_to_file("p1","test.csv", "a", ";", num_cars, circuit);

    //shared memory
    shmdt(circuit);

    exit(0);
}
