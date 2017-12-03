CC = clang
CFLAGS = -Wall -Wextra -O0 -g -fsanitize=address

.PHONY: all
all: build/main

clean:
	rm -f build/*


build/main: build/main.o build/gate.o build/wire.o build/circuit.o build/read_template.o
	$(CC) $(CFLAGS)  build/gate.o build/wire.o build/circuit.o build/read_template.o build/main.o  -o build/main

build/main.o: src/main.c
	$(CC) $(CFLAGS)  -c src/main.c -o build/main.o

build/gate.o: src/gate.c
	$(CC) $(CFLAGS)  -c src/gate.c -o build/gate.o

build/wire.o: src/wire.c
	$(CC) $(CFLAGS)  -c src/wire.c -o build/wire.o

build/circuit.o: src/circuit.c
	$(CC) $(CFLAGS)  -c src/circuit.c -o build/circuit.o

build/read_template.o: src/read_template.c
	$(CC) $(CFLAGS)  -c src/read_template.c -o build/read_template.o
