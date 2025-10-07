/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 11:30:19 by ral-haba          #+#    #+#             */
/*   Updated: 2025/10/05 12:39:14 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_config(t_config *cfg)
{
    if(!cfg)
        return ;
    cfg->north = NULL;
    cfg->south = NULL;
    cfg->west = NULL;
    cfg->east = NULL;
    cfg->floor[0] = -1;
    cfg->floor[1] = -1;
    cfg->floor[2] = -1;
    cfg->ceiling[0] = -1;
    cfg->ceiling[1] = -1;
    cfg->ceiling[2] = -1;
    cfg->map = NULL;
}

void    init_player(t_player *p)
{
    if (!p)
        return ;
    p->x = 0.0;
    p->y = 0.0;
    p->dir_x = -1.0; //the player is facing West
	p->dir_y = 0.0;
	p->plane_x = 0.0;
	p->plane_y = 0.66;
}

void    init_game(t_game *game)
{
    if(!game)
        return;
    game->mlx = NULL;
    game->win = NULL;
    init_config(&game->config);
    init_player(&game->player);
}

void init_ray(t_ray *ray)
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
}
