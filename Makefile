CC = clang
CFLAGS = -Wall -Wextra -Weverything  -O0 -g

CFLAGS += -fsanitize=address

OUTPUT = build/main

.PHONY: all
all: build/main

clean:
	rm -f build/*

remake: clean all

runclean: remake
	$(OUTPUT)


DEPS = port gate circuit wire read_template main

DEPS_O = $(DEPS:%=build/%.o)

build/main: $(DEPS_O)
	$(CC) $(CFLAGS)  $(DEPS_O) -o build/main

$(DEPS_O): build/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
