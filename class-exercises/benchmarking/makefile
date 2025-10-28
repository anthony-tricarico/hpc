# tells make to look for files ending in .c inside the src directory
vpath %.c src
# tells make to look for files ending in .h inside the include directory
vpath %.h include

vpath %.o build
# create a variable called CFLAGS including the flags that the compiler should accept
CFLAGS = -I include
# create a variable containing the name of the compiler to use
CC = mpicc

OBJ_DIR := build

# link all object files together and assign the output name (-o flag) to be the name
# of the target
benchmark: main.o get_time.o
	@echo "linking $@ ..."
	$(CC) $(CFLAGS) $^ -o $@

# compile main.c to an object with the name of the target (-o) 
# and skip linking (-c flag)
$(OBJ_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# same for get_time.c
$(OBJ_DIR)/get_time.o: get_time.c
	$(CC) $(CFLAGS) -c $< -o $@ 

solution: solution.c
	mpicc solution.c -o benchmark

s-send: solution_ssend.c
	mpicc solution_ssend.c -o benchmark
is-send: solution_issend.c
	mpicc solution_issend.c -o benchmark
head-2-head: solution_head_2_head.c
	mpicc solution_head_2_head.c -o benchmark
solution-csv: solution_csv.c
	mpicc solution_csv.c -o benchmark

test-time: get_time.c get_time.h
	gcc get_time.c -D TEST

# .PHONY targets
.PHONY: clean

clean:
	rm -rf start_cluster.sh.* a.out benchmark benchmark.* *.o
