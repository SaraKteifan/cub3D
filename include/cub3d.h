/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:51:58 by skteifan          #+#    #+#             */
/*   Updated: 2025/09/10 00:51:58 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

# include "MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 960
# define FOV_FACTOR 0.66
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.04

/******************************************************************************
*                                   Structs                                   *
******************************************************************************/

typedef enum e_wall
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_wall;

typedef struct s_config
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[3];
	int		ceiling[3];
	char	**map;
}	t_config;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*frame;
	t_config		*config;
	t_player		*player;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	mlx_texture_t	*textures[4];
}	t_game;

/* | Field                          | Purpose                                |
| ------------------------------ | -------------------------------------- |
| `dir_x`, `dir_y`               | Ray’s direction vector                 |
| `map_x`, `map_y`               | Current grid cell in map               |
| `side_dist_x`, `side_dist_y`   | Distance to next X/Y grid line         |
| `delta_dist_x`, `delta_dist_y` | Constant X/Y step distances            |
| `perp_wall_dist`               | Distance to the wall hit               |
| `step_x`, `step_y`             | Direction to step (left/right/up/down) |
| `hit`                          | Flag: did we hit a wall yet?           |
| `side`                         | Type of wall hit (X or Y)              |
 */
typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/******************************************************************************
*                             Function Prototypes                             *
******************************************************************************/

void		free_split(char **arr);
void		print_error_msg(char *msg);
void		init_game(t_game *game);
int			init_config(t_config **cfg);
void		init_player(t_player *p);
int			parse_file(char *filename, t_config *cfg);
int			parse_headers(int fd, t_config *cfg, char **line);
int			is_line_empty(const char *line);
int			is_map_line(char *line);
int			parse_map(int fd, t_config *cfg, char *line);
int			validate_map(t_config *cfg);
int			validate_map_closure(char **map, int px, int py);
char		*trim_spaces(char *str);
void		replace_tabs_with_spaces(char *line);
int			ft_is_number(char *str);
int			is_valid_rgb_value(char *part);
int			validate_color_parts(char **parts, int color[3]);
int			is_duplicate_color(char id, t_config *cfg);
int			validate_and_assign_texture(char **dst, char *line);
int			handle_header_value(char *trimmed, t_config *cfg);
void		free_config_and_exit(t_config *cfg, char *line);
void		free_config(t_config *cfg);
int			valid_color_commas(char *s);
char		*parse_texture(char *line);
int			parse_color(char *line, int color[3], t_config *cfg);

int			setup_game(t_game *game);
int			setup_player_from_map(t_config *config, t_player *player);
int			init_mlx(t_game *game);
void		init_ray(t_ray *ray);
int			render_frame(t_game *game);
void		run_dda(t_game *game, t_ray *ray);
void		draw_column(t_game *game, int x, t_ray *ray);
void		key_hook(void *param);
uint32_t	rgb_to_uint32(int rgb[3]);
uint32_t	get_tex_pixel_color(mlx_texture_t *tex, int tex_x, int tex_y);
void		close_hook(void *param);
void		clean_mlx_resources(t_game *game);
void		free_all_and_exit(t_game *game);
void		print_config_errors(t_config *cfg);

#endif
