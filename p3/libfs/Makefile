# Target library
lib := libfs.a
OBJ := disk.o fs.o

CC := gcc
CFLAGS := -Wall -Werror -g

all: $(lib)

libfs.a: $(OBJ)
	 ar rcs libfs.a fs.o disk.o

%.o: %.c
	@echo "CC $@"
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	echo "clean"
	rm -f  $(lib) $(OBJ) libfs.a

## TODO: Phase 1
