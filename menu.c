#include "libs/f1.h"

//TODO: help message
//TODO: .csv creation
//TODO: check param validity

int main(int argc, char *argv[]) {
    char race_name[10];
    char filename[51];
    char * mode = "a";
    int num_cars = 20;
    car circuit[20];

    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
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

    if (argc == 4 || strcmp(argv[2], "-tryouts") == 0) {
        if (strcmp(argv[3], "1") == 0) {
            mode = "w";
        }

        strcat(race_name, "S");
        strcat(race_name, argv[3]);

        for (int i = 0; i < num_cars; i++) init_car(&circuit[i], carIds[i]);

        //define condition for race finish
    } else if (argc == 4 || strcmp(argv[2], "-qualifiers") == 0) {
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
    }else if ()

//    for (int i = 0; i < num_cars; i++) {
//        init_car(&circuit[i], carIds[i]);
//    }
//
//    write_to_file("p1", "menu.csv", "w", ";", 20, circuit);
//    printf("name : %s\n", race_name);
//    int *order;
//    order = get_order("menu.csv", ";", "p1", 4);
//    for (int i = 0; i < 4; i++) {
//
//        printf("%d, %d\n", i, *(order + i));
//    }
}