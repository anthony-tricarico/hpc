main: main.c get_time.c get_time.h
	mpicc main.c get_time.c -o benchmark

solution: solution.c
	mpicc solution.c -o benchmark

test-time: get_time.c get_time.h
	gcc get_time.c -D TEST
