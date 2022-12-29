#include "f1.h"

void write_to_file(char* filename, char* mode, char* separator, int num_cars, car *bracket) {
    FILE *fpt;

    fpt = fopen(filename, mode);

    fprintf(fpt,"id%s s1%s s2 %ss3 %slap%s pitstop/crash\n",separator, separator, separator, separator, separator);

    for (int i = 0; i < num_cars; i++) {
        fprintf( fpt, "%2d", bracket[i].id);
        fprintf( fpt, "%s", separator);
        fprintf( fpt, "%-5.4g", bracket[i].s1);
        fprintf( fpt, "%s", separator);
        fprintf( fpt, "%-5.4g", bracket[i].s2);
        fprintf( fpt, "%s", separator);
        fprintf( fpt, "%-5.4g", bracket[i].s3);
        fprintf( fpt, "%s", separator);
        fprintf( fpt, "%-5.4g", bracket[i].best_lap);
        fprintf( fpt, "%s", separator);
        fprintf( fpt, "%s\n", bracket[i].state_pitstop_crash ? "true" : "false");
    }
}
//, car *bracket, int num_cars
void read_from_file(char* filename, char* separator, int num_fields) {
    const char* print_line(char* line, int num) {
        const char* tok;
        for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n")) {
            printf(" %s", tok);
            if (!--num) return tok;
        }
        return NULL;
    }

    FILE *fpt;
    char line[1024];
    fpt = fopen(filename, "r");

    while(fgets(line, 1024, fpt)){
        char* tmp = strdup(line);
        print_line(line, num_fields);
        printf("\n");
    }
}

void main(){
    read_from_file("test.csv", ";", 3);
}