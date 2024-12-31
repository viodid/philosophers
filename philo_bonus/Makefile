BINARY=philo
CODEDIRS=src
INCDIR=./include/

CC=gcc
# https://www.rapidtables.com/code/linux/gcc/gcc-g.html
OPT=-g3 -pthread
SAN=-fsanitize=leak
CFLAGS=-Wall -Wextra -Werror -I$(INCDIR) $(OPT)
CFILES=$(shell find $(CODEDIRS) -name '*.c')
OBJECTS = $(CFILES:.c=.o)

all: $(BINARY)

# https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean
$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(BINARY)

re: fclean all

diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git --no-pager diff --stat

.PHONY: all clean fclean re diff