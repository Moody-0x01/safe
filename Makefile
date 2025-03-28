LIB_DIR=lib
BIN_DIR=bin
MAIN=./src/main.c
SRCS=./src/salloc.c ./src/sstring.c ./src/sa_node_methods.c ./src/sallocator_methods.c
OBJS=$(SRCS:%.c=%.o)
SA=$(LIB_DIR)/libsa.a
CC=cc
LIBS=-L$(LIB_DIR) -lsa -ggdb
INCLUDE=-I./include/
NAME=$(BIN_DIR)/main
CFLAGS=-Wall -Wextra -Werror $(INCLUDE) -ggdb
AR=ar rsc
RM=rm -f

all: directories $(NAME)

directories:
	echo "Makin"
	mkdir -p $(LIB_DIR)
	mkdir -p $(BIN_DIR)
%.o: %.c $(directories)
	$(CC) $(CFLAGS) -c $^ -o $@
$(SA): $(OBJS)
	$(AR) $@ $?
$(NAME): $(SA) $(MAIN)
	$(CC) $(CFLAGS) $(MAIN) -o $@ $(LIBS)
clean:
	$(RM) $(OBJS)
	$(RM) $(SA)
fclean: clean
	$(RM) $(NAME)
run: $(NAME)
	@$(NAME)

re: fclean all
.PHONY: re fclean clean bonus
