CC = gcc
CFLAGS = -Wall -std=c17
LDLIBS = -lMLV -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = Quadtree

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDLIBS)
	rm -f $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
