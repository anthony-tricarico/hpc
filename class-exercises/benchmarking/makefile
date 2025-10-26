main: main.c get_time.c get_time.h
	mpicc main.c get_time.c -std=gnu99 -o benchmark

solution: solution.c
	mpicc solution.c -o benchmark

solution-csv: solution_csv.c
	mpicc solution_csv.c -o benchmark

test-time: get_time.c get_time.h
	gcc get_time.c -D TEST
