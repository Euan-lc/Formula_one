#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "car.h"

void bubble_sort(car *list, int car_count);

void best_sector(car *list, int car_count);

float genTime(float lower, float upper);

void init_car(car *ptr, int carId);

void lap_car(car *ptr, int (*f)(int));

void display_scores(car *circuit, int car_count);

void write_to_file(char* race, char* filename, char* mode, char* separator, int num_cars, car *bracket);

void load_results(char* filename, char* separator, char* race, int num_cars, car* bracket0);

int * get_order(char* filename, char* separator, char* race, int num_cars);

int * compile_grid(char * filename);
