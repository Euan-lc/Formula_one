#include "f1.h"

void display_scores(car *circuit, int car_count){
    printw("| id |   s1  |   s2  |   s3  |  lap  | pitstop/crash \n|----|-------|-------|-------|-------|---------------\n");

    for (int i = 0; i < car_count; i++) {
        printw("| %2d | ", circuit[i].id);
        if (circuit[i].has_best_s1)attron(COLOR_PAIR(1));
        printw("%-5.4g", circuit[i].s1);
        if (circuit[i].has_best_s1)attroff(COLOR_PAIR(1));
        printw(" | ");
        if (circuit[i].has_best_s2)attron(COLOR_PAIR(1));
        printw("%-5.4g", circuit[i].s2);
        if (circuit[i].has_best_s2)attroff(COLOR_PAIR(1));
        printw(" | ");
        if (circuit[i].has_best_s3)attron(COLOR_PAIR(1));
        printw("%-5.4g", circuit[i].s3);
        if (circuit[i].has_best_s3)attroff(COLOR_PAIR(1));
        printw(" | %-5.4g\n", circuit[i].best_lap);
        printw(" | %B\n", circuit[i].state_pitstop_crash);
    }
}