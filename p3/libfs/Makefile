# Target library
lib := libfs.a
OBJ := disk.o fs.o

CC := gcc
LC := ar rcs
CFLAGS := -Wall -Werror

## Debug flag
ifneq ($(D),1)
CFLAGS    += -O2
else
CFLAGS    += -g
endif

ifneq ($(V),1)
Q = @
endif

all: $(lib)

deps := $(patsubst %.o,%.d,$(OBJ))
-include $(deps)

libfs.a: $(OBJ)
	@echo "LC $@"
	$(LC) $@ $(OBJ)

%.o: %.c
	@echo "CC $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	echo "clean"
	$(Q)rm -f $(OBJ) $(lib) $(deps)

## TODO: Phase 1
