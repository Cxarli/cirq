CC = clang
CFLAGS = -Wall -Wextra -Weverything  -O0 -g

CFLAGS += -fsanitize=address

OUTPUT = build/main

.PHONY: all
all: build/main

clean:
	rm -f build/*

remake: clean all

cleanrun: remake
	@echo -e "\n\n"
	$(OUTPUT)


DEPS = bool circuit gate port read_template wire main

DEPS_O = $(DEPS:%=build/%.o)

build/main: $(DEPS_O)
	$(CC) $(CFLAGS)  $(DEPS_O) -o $(OUTPUT)

$(DEPS_O): build/%.o: src/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
