/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 11:30:19 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/30 11:22:51 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_config(t_config **cfg)
{
	*cfg = malloc(sizeof(t_config));
	if (!*cfg)
	{
		print_error_msg("Malloc failed.");
		return (1);
	}
	(*cfg)->north = NULL;
	(*cfg)->south = NULL;
	(*cfg)->west = NULL;
	(*cfg)->east = NULL;
	(*cfg)->floor[0] = -1;
	(*cfg)->floor[1] = -1;
	(*cfg)->floor[2] = -1;
	(*cfg)->ceiling[0] = -1;
	(*cfg)->ceiling[1] = -1;
	(*cfg)->ceiling[2] = -1;
	(*cfg)->map = NULL;
	(*cfg)->map_width = 10;
	(*cfg)->map_height = 10;
	return (0);
}

void	init_player(t_player *p)
{
	if (!p)
		return ;
	p->x = 0.0;
	p->y = 0.0;
	p->dir_x = 0.0;
	p->dir_y = 0.0;
	p->plane_x = 0.0;
	p->plane_y = 0.0;
}

void	init_game(t_game *game)
{
	if (!game)
		return ;
	game->mlx = NULL;
	game->frame = NULL;
	game->player = NULL;
	game->config = NULL;
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->textures[NORTH] = NULL;
	game->textures[SOUTH] = NULL;
	game->textures[WEST] = NULL;
	game->textures[EAST] = NULL;
	game->minimap = NULL;
}

void	init_ray(t_ray *ray)
{
	if (!ray)
		return ;
	ray->dir_x = 0.0;
	ray->dir_y = 0.0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->side_dist_x = 0.0;
	ray->side_dist_y = 0.0;
	ray->delta_dist_x = 0.0;
	ray->delta_dist_y = 0.0;
	ray->perp_wall_dist = 0.0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}
