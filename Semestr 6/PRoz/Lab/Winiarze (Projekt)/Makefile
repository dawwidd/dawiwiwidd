SOURCES=$(wildcard *.cpp)
HEADERS=$(SOURCES:.c=.h)
FLAGS=-DDEBUG -g

all: main

main: $(SOURCES) $(HEADERS)
	mpic++ $(SOURCES) $(FLAGS) -o a.out

clean: clean

clear:
	rm a.out

run: main
	mpirun --oversubscribe -np 10 ./a.out

run-vms: main
	mpirun-vms -np 10 a.out

run-xterm: main
	mpirun --oversubscribe -np 10 xterm -hold -e ./a.out