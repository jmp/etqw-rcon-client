CC=gcc
CFLAGS=-s -O2 -Wextra -Wall -pedantic -ansi -Wfloat-equal -Wundef -Wshadow \
	-Wwrite-strings -Wconversion -Wsign-compare -Wstrict-prototypes \
	-Wold-style-definition -Wredundant-decls
CFILES=etqwrcon.c
TARGET=etqwrcon

all: $(CFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILES)

clean:
	rm -f $(TARGET)

.PHONY: clean
