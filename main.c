#include "libs/f1.h"
#include <errno.h>

extern int errno ;

//TODO: check param validity

int main(int argc, char *argv[]) {
    char race_name[10];
    char *filename;
    char * mode = "a";
    int num_cars = 20;
    int shmid, cpid, shmkey = 4101;//ca casse parfois a cause de ca

    //shared memory
    shmid = shmget(shmkey, num_cars * sizeof(car), IPC_CREAT | 0666);
    perror("");
    car *circuit = shmat(shmid, 0, 0);


    if (argc == 1 || strcmp(argv[1], "-h") == 0) {
        // Print the help message
        printf("Usage: ./Formula_one [weekend] [race_type] [race_number] [num_turns/time]\n\n");

        printf("  -h     display this help message\n\n");

        printf("weekend is the name of the file which will store the race results, it can be up to 50 characters long\n\n");

        printf("race types :\n");
        printf("  -tryouts\n");
        printf("  -qualifiers\n");
        printf("  -sprint\n");
        printf("  -final\n\n");
        printf("race_number :\n");
        printf("race_number is for tryout and qualifiers and is from 1 to 3\n\n");

        printf("num_turns :\n");
        printf("num_turns is for sprint or final and determines the number of turns the cars have to complete.\n");

        return 0;
    }

    filename = argv[1];

    if (argc == 4 && strcmp(argv[2], "-tryouts") == 0) {
        if (strcmp(argv[3], "1") == 0) {
            mode = "w";
        }
        strcat(race_name, "S");
        strcat(race_name, argv[3]);
        printf("i'm here\n");

        for (int i = 0; i < num_cars; i++) {
            printf("i'm here\n");
            init_car(&circuit[i], carIds[i]);
        }

        //define condition for race finish
    } else if (argc == 4 && strcmp(argv[2], "-qualifiers") == 0) {
        int *order;

        strcat(race_name, "Q");
        strcat(race_name, argv[3]);
        if(strcmp(race_name, "Q1") == 0) {
            num_cars = 20;
            for (int i = 0; i < num_cars; i++) init_car(&circuit[i], carIds[i]);
        } else if(strcmp(race_name, "Q2") == 0){
            num_cars = 15;
            order = get_order(filename, ";", "Q1", num_cars);
            for (int i = 0; i < num_cars; i++) init_car(&circuit[i], *(order + i));
            read_from_file(filename, ";", "Q1", 20, circuit, 5);
        } else if(strcmp(race_name, "Q3") == 0){
            num_cars = 10;
            order = get_order(filename, ";", "Q2", num_cars);
            for (int i = 0; i < num_cars; i++) init_car(&circuit[i], *(order + i));
            read_from_file(filename, ";", "Q1", 20, circuit, 5);
        }

        //define condition for race finish
    }
    printf("i'm here\n");

    //display
    initscr();
    start_color();
    init_pair(1,COLOR_MAGENTA, COLOR_BLACK);

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

        write_to_file(race_name,filename, mode, ";", num_cars, circuit);

        //shared memory
        shmctl(shmid, IPC_RMID, NULL);

        //display
        getch();
        endwin();
    }
    shmdt(circuit);
}