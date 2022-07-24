CC=gcc
CFLAGS=-I.
DEPS = MemoryManagement.h Block.h
OBJ = main.o MemoryManagement.o Block.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJ)
	${CC} -o $@ $^ $(CFLAGS)

clean:
	rm *.o
	rm build
