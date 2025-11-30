/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:48:59 by skteifan          #+#    #+#             */
/*   Updated: 2025/11/26 21:56:34 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_wall_orientation(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->step_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

int	compute_tex_x(t_game *game, t_ray *ray, int wall_orient)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player->y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player->x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)game->textures[wall_orient]->width);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex_x = game->textures[wall_orient]->width - tex_x - 1;
	return (tex_x);
}

void	draw_ceiling_and_floor(t_game *game, int x, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		mlx_put_pixel(game->frame, x, y, game->ceiling_color);
		y++;
	}
	y = ray->draw_end + 1;
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->frame, x, y, game->floor_color);
		y++;
	}
}

void	draw_wall_texture(t_game *game, int x, t_ray *ray, int wall_orient)
{
	int		y;
	int		tex_x;
	double	tex_pos;
	double	step;
	int		tex_y;

	y = ray->draw_start;
	tex_x = compute_tex_x(game, ray, wall_orient);
	step = (double)game->textures[wall_orient]->height
		/ (double)ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)game->textures[wall_orient]->height)
			tex_y = (int)game->textures[wall_orient]->height - 1;
		tex_pos += step;
		mlx_put_pixel(game->frame, x, y,
			get_tex_pixel_color(game->textures[wall_orient], tex_x, tex_y));
		y++;
	}
}

void	draw_column(t_game *game, int x, t_ray *ray)
{
	int	wall_orient;

	wall_orient = get_wall_orientation(ray);
	draw_ceiling_and_floor(game, x, ray);
	draw_wall_texture(game, x, ray, wall_orient);
}
