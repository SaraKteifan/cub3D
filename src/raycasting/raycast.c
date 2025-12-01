/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:42:41 by skteifan          #+#    #+#             */
/*   Updated: 2025/12/01 11:28:48 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void	compute_step_and_side_dist(t_player *player, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void	compute_perp_wall_dist(t_player *player, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
}

void	compute_wall_height(t_ray *ray)
{
	if (ray->perp_wall_dist < 0.0001f)
		ray->perp_wall_dist = 0.0001f;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

int	render_frame(t_game *game)
{
	int		x;
	double	camera_x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray);
		camera_x = (2 * x / (double)WIDTH) - 1.0;
		ray.dir_x = game->player->dir_x + game->player->plane_x * camera_x;
		ray.dir_y = game->player->dir_y + game->player->plane_y * camera_x;
		ray.map_x = (int)game->player->x;
		ray.map_y = (int)game->player->y;
		compute_delta_dist(&ray);
		compute_step_and_side_dist(game->player, &ray);
		run_dda(game, &ray);
		compute_perp_wall_dist(game->player, &ray);
		compute_wall_height(&ray);
		draw_column(game, x, &ray);
		x++;
	}
	return (0);
}
