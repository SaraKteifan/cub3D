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

#include "../lib/libft/libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/******************************************************************************
*                                   Structs                                   *
******************************************************************************/
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
	void		*mlx;
	void		*win;
	t_config	config;
	t_player	player;
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
}	t_ray;




/******************************************************************************
*                             Function Prototypes                             *
******************************************************************************/

void	free_split(char **arr);
void    exit_str(char *msg);
void	init_config(t_config *cfg);
int 	parse_file(char *filename, t_config *cfg);
int		parse_headers(int fd, t_config *cfg, char **line);
int		is_line_empty(const char *line);
int		is_map_line(char *line);
int		parse_map(int fd, t_config *cfg, char *line);
int		validate_map(t_config *cfg);

#endif
