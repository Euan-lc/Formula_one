#include "libs/f1.h"

//TODO: help message
//TODO: .csv creation
//TODO: check param validity

int main(int argc, char *argv[]) {
    char race_name[10], char filename[51];
    int num_cars;
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

    if (argc == 4 && strcmp(argv[2], "-tryouts") == 0) {
        if (strcmp(argv[3], "1") == 0) {
            //create file
        }

        strcat(race_name, "P");
        strcat(race_name, argv[3]);

        //        for (int i = 0; i < num_cars; i++) init_car(&circuit[i], carIds[i]);

        //define condition for race finish
    }
    else if (argc == 4 && strcmp(argv[2], "-qualifiers") == 0) {
        strcat(race_name, "Q");
        strcat(race_name, argv[3]);

        if(strcmp(race_name, "Q2") == 0){
            num_cars = 15;
            read_from_file(filename, ";", "Q1", 15, circuit);
        } else if(strcmp(race_name, "Q3") == 0){
            num_cars = 10;
            read_from_file(filename, ";", "Q2", 10, circuit);
        }

        //define condition for race finish
    }
    printf("name : %s\n", race_name);
}