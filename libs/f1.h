#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>
#include "car.h"

void bubble_sort(car *list, int car_count);

void best_sector(car *list, int car_count);