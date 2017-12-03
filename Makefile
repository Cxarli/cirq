CC = clang
CFLAGS = -Wall -Wextra -Weverything  -O0 -g -fsanitize=address

.PHONY: all
all: build/main

clean:
	rm -f build/*


DEPS = gate circuit wire read_template main

DEPS_O = $(DEPS:%=build/%.o)

build/main: $(DEPS_O)
	$(CC) $(CFLAGS)  $(DEPS_O) -o build/main

$(DEPS_O): build/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
