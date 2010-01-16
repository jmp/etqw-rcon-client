CC=gcc
CFLAGS=-s -O2 -ansi -Wextra -Wall -pedantic -ansi -Wfloat-equal -Wundef \
	-Wshadow -Wwrite-strings -Wconversion -Wsign-compare \
	-Wstrict-prototypes -Wold-style-definition -Wredundant-decls \
	-D_POSIX_C_SOURCE=200112L # required for POSIX.1-2001 functions
CFILES=etqwrcon.c
TARGET=etqwrcon

all: $(CFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILES)

clean:
	rm -f $(TARGET)

.PHONY: clean
