SOURCES=main.c queue_bfs.c node.c edge.c path.c network.c output.c dinic.c
LIBS=
TARGET=dinic
CC=gcc
CFLAGS=-ansi -Wall -pedantic
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS) .depend

docs:
	doxygen Doxyfile


-include .depend

.depend: $(SOURCES) *.h
	gcc -MM $(SOURCES) >.depend

$(TARGET): $(OBJECTS) $(LIBS)
	$(CC) -o $@ $^

