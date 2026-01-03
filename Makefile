NAME    = cub3D
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

SRC_PATH    = src/
OBJ_PATH    = build/
INCLUDE     = include/
LIBFT_PATH  = lib/libft/
MLX_PATH    = lib/MLX42
INCLUDES    = -I$(INCLUDE) -I$(LIBFT_PATH) -I$(MLX_PATH)/include

LIBFT       = $(LIBFT_PATH)libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

MLX42       = $(MLX_PATH)/build/libmlx42.a
MLX42_FLAGS = -L$(MLX_PATH)/build -lmlx42 -lm -ldl -lglfw -pthread

SRC_FILES   = main\
			parsing/parse_file\
			parsing/parse_headers\
			parsing/parse_texture\
			parsing/parse_colors\
			parsing/parse_map\
			parsing/validate_map\
			parsing/validate_map_closure\
			parsing/parse_utils\
			init/init\
			init/init_game\
			init/init_player\
			init/init_mlx\
			raycasting/raycast\
			raycasting/dda\
			rendering/draw\
			rendering/hooks\
			rendering/colors\
			free\
			utils\

SRC         = $(addprefix $(SRC_PATH), $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(addprefix $(OBJ_PATH), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) $(LIBFT_FLAGS) $(MLX42_FLAGS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH) --no-print-directory -s

$(MLX42):
	@cmake -B $(MLX_PATH)/build -S $(MLX_PATH) > /dev/null
	@make -C $(MLX_PATH)/build -j4 --no-print-directory -s

bonus: all

build:
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@rm -rf $(MLX_PATH)/build

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re
