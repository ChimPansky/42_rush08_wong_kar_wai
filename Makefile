NAME = 2048

all: $(NAME)

SOURCE_DIR = src
BUILD_DIR = build

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -MMD -g

IFLAGS = -Iinclude
LFLAGS = -lncursesw
#MAKEFLAGS	= -j$(nproc) --no-print-directory

include libft/colors.mk
LIBFT = libft/libft.a
$(LIBFT):
	@make -C libft all clean
IFLAGS += -Ilibft
LFLAGS += -Llibft -lft

.PHONY: lft
lft:
	@make -C libft all clean

CFILES += \
	ft_2048.c \
	game.c \
	grid.c \
	position.c

SRC = $(addprefix $(SOURCE_DIR)/,$(CFILES))
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

$(BUILD_DIR)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -fr $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind:
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME)

.PHONY: all bonus clean fclean re test
