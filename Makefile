NAME    = cub3D
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRC_PATH    = src/
OBJ_PATH    = build/
INCLUDE     = include/
LIBFT_PATH  = lib/libft/
GNL_PATH    = lib/GNL/

LIBFT       = $(LIBFT_PATH)libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

SRC_FILES   = main\
			parsing/parse_file\
			parsing/parse_headers\
			parsing/parse_map\
			parsing/parse_utils\
			parsing/validate_map\
			free\
			init\
			utils\

SRC         = $(addprefix $(SRC_PATH), $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_PATH), $(addsuffix .o, $(SRC_FILES)))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $@ $(OBJ) $(LIBFT_FLAGS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH) --no-print-directory

build:
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean --no-print-directory

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re
