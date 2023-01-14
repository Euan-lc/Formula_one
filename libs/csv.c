#include "f1.h"

void write_to_file(char* race, char* filename, char* mode, char* separator, int num_cars, car *bracket) {
    FILE *fpt;
    char * path;
    path = strdup(filename);
    strcat(path, "/");
    strcat(path, race);
    strcat(path, ".csv");

    fpt = fopen(path, mode);

    fprintf(fpt,"%s\nid%s best s1%s best s2 %s best s3 %s best lap\n",race, separator, separator, separator, separator);

    for (int i = 0; i < num_cars; i++) {
        fprintf( fpt, "%2d", bracket[i].id);
        fprintf( fpt, "%s", separator);
        fprintf( fpt, "%-5.4g", bracket[i].best_s1);
        fprintf( fpt, "%s", separator);
        fprintf( fpt, "%-5.4g", bracket[i].best_s2);
        fprintf( fpt, "%s", separator);
        fprintf( fpt, "%-5.4g", bracket[i].best_s3);
        fprintf( fpt, "%s", separator);
        fprintf( fpt, "%-5.4g\n", bracket[i].best_lap);
    }
    fclose( fpt );
}

void fill_car(char line[], char* separator, car *temp) {
    const char* tok;

    init_car(temp, 0);

    tok = strtok(line, separator);
    temp->id = atoi(tok);
    tok = strtok(NULL, separator);
    temp->best_s1 = atof(tok);
    tok = strtok(NULL, separator);
    temp->best_s2 = atof(tok);
    tok = strtok(NULL, separator);
    temp->best_s3 = atof(tok);
    tok = strtok(NULL, separator);
    temp->best_lap = atof(tok);
}

void load_results(char* filename, char* separator, char* race, int num_cars, car* bracket) {
    FILE *fpt;
    char line[1024];
    car test;
    char * path;

    path = strdup(filename);
    strcat(path, "/");
    strcat(path, race);
    strcat(path, ".csv");

    fpt = fopen(path, "r");

    while(fgets(line, 1024, fpt)){
        char* tmp = strdup(line);
        const char* tok = strtok(tmp, "\n");
        if(!strcmp(tok,race)){
            fgets(line, 1024, fpt);
            break;
        }
    }

    for(int i = 0; i < num_cars ; i++){
        fgets(line, 1024, fpt);
        fill_car(line, separator, &test);
        bracket[i] = test;
    }

    fclose( fpt );
}

int * get_order(char* filename, char* separator, char* race, int num_cars) {
    static int  order[20];
    FILE *fpt;
    char line[1024];
    char * path;
    path = strdup(filename);
    strcat(path, "/");
    strcat(path, race);
    strcat(path, ".csv");

    fpt = fopen(path, "r");

    while(fgets(line, 1024, fpt)){
        char* tmp = strdup(line);
        const char* tok = strtok(tmp, "\n");
        if(strcmp(tok,race) == 0){
            fgets(line, 1024, fpt);
            break;
        }
    }

    for(int i = 0; i < num_cars ; ++i){
        fgets(line, 1024, fpt);
        char* tmp = strdup(line);
        order[i] = atoi(strtok(tmp, separator));
    }
    fclose( fpt );
    return order;
}

int * compile_grid(char * filename){
    static int grid[20];
    int *order;

    order = get_order(filename, ";", "Q1", 20);
    for (int i = 19; i > 14; --i) grid[i] = order[i];
    order = get_order(filename, ";", "Q2", 20);
    for (int i = 14; i > 9; --i) grid[i] = order[i];
    order = get_order(filename, ";", "Q3", 20);
    for (int i = 9; i >= 0; --i) grid[i] = order[i];
    
    return grid;
}