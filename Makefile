CC = gcc
CFLAGS = -Wall -O2 -fPIC

LIB_SRC = matrix_operations.c
LIB_OBJ = matrix_operations.o
HEADER = matrix_operations.h
MAIN = main.c
TARGET = main

STATIC_LIB = libmatrix_operations.a
SHARED_LIB = libmatrix_operations.so

all: $(TARGET)

$(TARGET): $(MAIN) $(SHARED_LIB)
	$(CC) $(CFLAGS) -o $@ $(MAIN) -L. -lmatrix_operations -Wl,-rpath=.

$(LIB_OBJ): $(LIB_SRC) $(HEADER)
	$(CC) $(CFLAGS) -c $(LIB_SRC)

$(STATIC_LIB): $(LIB_OBJ)
	ar rcs $@ $^

$(SHARED_LIB): $(LIB_OBJ)
	$(CC) -shared -o $@ $^

clean:
	rm -f *.o *.a *.so $(TARGET)

.PHONY: all clean
