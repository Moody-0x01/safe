# TODO: Add my printf
LIBFT_DIR=./src/libft
PF_DIR=./src/ft_printf
LIB_DIR=lib
LIBFT=$(LIB_DIR)/libft.a
LIBPF=$(LIB_DIR)/libftprintf.a
BIN_DIR=bin
MAIN=./src/main.c
SRCS=./src/salloc.c ./src/core/sstring_array.c ./src/core/sstring_split.c ./src/core/sstring.c ./src/sa_node_methods.c ./src/sallocator_methods.c ./src/panic.c
OBJS=$(SRCS:%.c=%.o)
SA=$(LIB_DIR)/libsa.a
CC=cc
LIBS=-L$(LIB_DIR) -lsa -lft -lftprintf
INCLUDE=-I./include/
NAME=$(BIN_DIR)/main
CFLAGS=-Wall -Wextra -Werror $(INCLUDE)
AR=ar rsc
RM=rm -f

all: directories $(NAME)

directories:
	echo "Makin"
	mkdir -p $(LIB_DIR)
	mkdir -p $(BIN_DIR)
%.o: %.c $(directories)
	$(CC) $(CFLAGS) -c $^ -o $@
$(LIBFT): $(LIBFT_DIR)
	make -C $(LIBFT_DIR)
$(LIBPF): $(PF_DIR)
	make -C $(PF_DIR)
$(SA): $(OBJS)
	$(AR) $@ $?
$(NAME): $(LIBPF) $(LIBFT) $(SA) $(MAIN)
	$(CC) $(CFLAGS) $(MAIN) -o $@ $(LIBS)
clean:
	make -C $(LIBFT_DIR) clean
	make -C $(PF_DIR) clean
	$(RM) $(OBJS)
	$(RM) $(SA)
fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(PF_DIR) fclean
	$(RM) $(NAME)
run: $(NAME)
	@$(NAME)

re: fclean all
.PHONY: re fclean clean bonus
