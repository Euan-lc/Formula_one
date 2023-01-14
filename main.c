#include "libs/f1.h"
#include <errno.h>

extern int errno ;

typedef int (*stop_race_T)(int tot, int laps);

//TODO: check param validity

int help(){
    // Print the help message
    printf("Usage: ./Formula_one [weekend] [race_type] [race_number] [circuit]\n\n");

    printf("  -h     display this help message\n\n");

    printf("weekend is the name of the file which will store the race results, it can be up to 50 characters long\n\n");

    printf("race types :\n");
    printf("  -tryouts\n");
    printf("  -qualifiers\n");
    printf("  -sprint\n");
    printf("  -final\n\n");
    printf("race_number :\n");
    printf("race_number is for tryout and qualifiers and is from 1 to 3\n\n");

    printf("circuit :\n");
    printf("circuit is for sprint or final and determines the number of turns the cars have to complete.\n");

    exit(0);
}

int stop_tryouts (int tot, int laps){
    if(tot>=3600)return 1;
    else return 0;
}

int stop_Q1 (int tot, int laps){
    if(tot>=(18 * 60))return 1;
    else return 0;
}

int stop_Q2 (int tot, int laps){
    if(tot>=(15 * 60))return 1;
    else return 0;
}

int stop_Q3 (int tot, int laps){
    if(tot>=(12 * 60))return 1;
    else return 0;
}

int stop_final (int tot, int laps){
    if(laps>=70)return 1;
    else return 0;
}

int stop_sprint (int tot, int laps){
    if(laps>=30)return 1;
    else return 0;
}

int main(int argc, char *argv[]) {
    char race_name[10];
    char *filename;
    char * mode = "a";
    int num_cars = 20, total_cars = 20;
    int shmid, semid1, semid2, semid3, cpid, shmkey = 4101, semkey1 = 234, semkey2, semkey3;//ca casse parfois a cause de ca
    car * buffer = malloc(total_cars * sizeof(car));
    stop_race_T stop_race_ptr;
    struct sembuf sopw, sopd, sopi;
    union semun set_val;

    sopw.sem_num = 0;
    sopw.sem_op = 0;
    sopw.sem_flg = 0;

    sopd.sem_num = 0;
    sopd.sem_op = -1;
    sopd.sem_flg = 0;

    sopi.sem_num = 0;
    sopi.sem_op = 1;
    sopi.sem_flg = 0;

    //shared memory
    shmid = shmget(shmkey, total_cars * sizeof(car), IPC_CREAT | 0666);
    car *circuit = shmat(shmid, 0, 0);

    if (argc == 1 || strcmp(argv[1], "-h") == 0) help();
    filename = argv[1];

    if (argc == 4 && strcmp(argv[2], "-tryouts") == 0) {
        if (strcmp(argv[3], "1") == 0) {
            mkdir(filename, 0700);
            char * path;
            path = strdup(filename);
            strcat(path, "/bests.csv");
            for (int i = 0; i < num_cars; i++) init_car(&buffer[i], carIds[i]);
            write_to_file("bests", filename, "w", ";", total_cars, buffer);
        }
        strcat(race_name, "P");
        strcat(race_name, argv[3]);

        for (int i = 0; i < num_cars; i++) {
            init_car(&circuit[i], carIds[i]);
        }

        //define condition for race finish
        stop_race_ptr = stop_tryouts;

    } else if (argc == 4 && strcmp(argv[2], "-qualifiers") == 0) {
        int *order;

        strcat(race_name, "Q");
        strcat(race_name, argv[3]);
        if(strcmp(race_name, "Q1") == 0) {
            num_cars = 20;
            for (int i = 0; i < num_cars; i++) init_car(&circuit[i], carIds[i]);
            stop_race_ptr = stop_Q1;
        } else if(strcmp(race_name, "Q2") == 0){
            num_cars = 15;
            order = get_order(filename, ";", "Q1", num_cars);
            for (int i = 0; i < num_cars; i++) {
                init_car(&circuit[i], *(order + i));
            }
            stop_race_ptr = stop_Q2;
        } else if(strcmp(race_name, "Q3") == 0){
            num_cars = 10;
            order = get_order(filename, ";", "Q2", num_cars);
            for (int i = 0; i < num_cars; i++) {
                init_car(&circuit[i], *(order + i));
            }
            stop_race_ptr = stop_Q3;
        }
    } else if (strcmp(argv[2], "-final") == 0) {
        int * order;
        strcat(race_name, "final");
        num_cars = 20;
        order = compile_grid(filename);
        for (int i = 0; i < num_cars; i++) {
            init_car(&circuit[i], *(order + i));
        }
        stop_race_ptr = stop_final;
    }

    for (int i = 0; i < num_cars; i++) {
        if ((cpid = fork()) == 0) {
            car child;
            child = circuit[i];
            sleep(1);
            semid1 = semget(semkey1, 1, 0);
            semid2 = semget(semkey2, 1, 0);
//            semid3 = semget(semkey3, 1, 0);
            //generate seed for rand based on
            srand48(time(0) + child.id);
            semop(semid2, &sopw, 1);

            while(lap_car(&circuit[i], stop_race_ptr)){
//                sleep(1);//change that
//                printf("%d\n", child.id);
                semop(semid1, &sopd, 1);
            }
//            semop(semid3, &sopi, 1);
            exit(0);
        }
    }

    if(cpid != 0){
//        int sem3_val = 0;
        semid1 = semget(semkey1, 1, IPC_CREAT | 0600);
        semid2 = semget(semkey2, 1, IPC_CREAT | 0600);
//        semid3 = semget(semkey3, 1, IPC_CREAT | 0600);
        if(semid1 == -1 || semid2 == -1){
            perror("");
        }

        set_val.val = num_cars;
        semctl(semid1, 0, SETVAL, set_val);

        set_val.val = 1;
        semctl(semid2, 0, SETVAL, set_val);

//        set_val.val = 0;
//        semctl(semid3, 0, SETVAL, set_val);
        //display
        initscr();
        start_color();
        init_pair(1,COLOR_MAGENTA, COLOR_BLACK);
        halfdelay(5);

        for(int i = 0; i < 10; i++) {
            buffer = malloc(num_cars * sizeof(car));

            semop(semid1, &sopw, 1);
            set_val.val = 1;
            semctl(semid2, 0, SETVAL, set_val);
            memcpy(buffer,circuit,num_cars * sizeof(car));
            set_val.val = num_cars;
            semctl(semid1, 0, SETVAL, set_val);
            semop(semid2, &sopd, 1);

            bubble_sort(buffer, num_cars);
            printw("%d\n", i);
            display_scores(buffer, num_cars);

            getch();
            erase();
            refresh();
//            sem_getvalue(semid3,&sem3_val);
//            if(sem3_val == num_cars){
//                break;
//            }
        }

        //sort then write to file
        memcpy(buffer,circuit,num_cars * sizeof(car));
        bubble_sort(buffer, num_cars);
        write_to_file(race_name,filename, mode, ";", num_cars, buffer);

        //update best results
//        buffer = malloc(total_cars * sizeof(car));
//        load_results(filename, ";", "bests", total_cars, buffer);
//
//        rearrange(buffer, 20);
//        rearrange(circuit, 20);
//
//        for(int i = 0; i < num_cars; i++) {
//            printf("%d\n", i);
//            if(circuit[i].best_s1 < buffer[i].best_s1)buffer[i].best_s1 = circuit[i].best_s1;
//            if(circuit[i].best_s2 < buffer[i].best_s2)buffer[i].best_s2 = circuit[i].best_s2;
//            if(circuit[i].best_s3 < buffer[i].best_s3)buffer[i].best_s3 = circuit[i].best_s3;
//            if(circuit[i].best_lap < buffer[i].best_lap)buffer[i].best_lap = circuit[i].best_lap;
//        }
//        write_to_file("bests",filename, "w", ";", num_cars, buffer);

        //shared memory
        shmctl(shmid, IPC_RMID, NULL);

        //semaphore
        semctl(semid1, 0, IPC_RMID);
        semctl(semid2, 0, IPC_RMID);

        //display
        getch();
        endwin();
    }
    shmdt(circuit);
}