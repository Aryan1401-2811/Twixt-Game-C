CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC = main.c board.c game.c
OBJ = $(SRC:.c=.o)

all: a.out

a.out: $(OBJ)
	$(CC) $(CFLAGS) -o a.out $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o a.out
