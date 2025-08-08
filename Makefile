SRCS=./src/Token.c ./src/Parse.c ./src/Eval.c
OBJS=$(SRCS:%.c=%.o)
NAME=parser
CC=cc
LIBS=
INCLUDE=-I./include/
MAIN=./src/main.c
IN_PMAIN=./src/InPlace.c
IN_PNAME=parser_nomem
CFLAGS=-Wall -Wextra -Werror $(INCLUDE)
RM=rm -f

all: $(NAME) $(IN_PNAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MAIN) $(OBJS) -o $@ $(LIBS)
$(IN_PNAME): $(IN_PMAIN)
	$(CC) $(CFLAGS) $(IN_PMAIN) -o $@ $(LIBS)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
	$(RM) $(IN_PNAME)
re: fclean all
.PHONY: re fclean clean bonus

