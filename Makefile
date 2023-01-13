main: main.c libs/car.h libs/display.c libs/vroum.c libs/sort.c libs/csv.c
	gcc libs/display.c -c
	gcc libs/sort.c -c
	gcc libs/vroum.c -c
	gcc libs/csv.c -c
	gcc main.c -lncurses display.o sort.o vroum.o csv.o -o main
clean:
	rm -f main
	rm -f display.o
	rm -f vroum.o
	rm -f sort.o
	rm -f csv.o
	rm -f circuit
	rm -f test.csv
menu: libs/f1.h menu.c libs/csv.c libs/vroum.c
	gcc libs/vroum.c -c
	gcc libs/csv.c -c
	gcc menu.c csv.o vroum.o -o menu