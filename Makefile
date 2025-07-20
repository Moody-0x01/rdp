SRCS=./src/Token.c ./src/Parse.c ./src/Eval.c
OBJS=$(SRCS:%.c=%.o)
NAME=parser
CC=cc
LIBS=
INCLUDE=-I./include/
MAIN=./src/main.c
CFLAGS=-Wall -Wextra -Werror $(INCLUDE)
RM=rm -f

all: $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MAIN) $(OBJS) -o $@ $(LIBS)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: re fclean clean bonus

