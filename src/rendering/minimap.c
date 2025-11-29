/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:43:42 by skteifan          #+#    #+#             */
/*   Updated: 2025/11/29 22:40:13 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game, mlx_image_t *mm, int tile)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	x = game->player->x * tile;
	y = game->player->y * tile;
	dy = -2;
	while (dy <= 2)
	{
		dx = -2;
		while (dx <= 2)
		{
			mlx_put_pixel(mm, x + dx, y + dy, 0xFF0000FF);
			dx++;
		}
		dy++;
	}
}

void	draw_tile(t_game *game, int tile, int x, int y)
{
	int			i;
	int			j;
	uint32_t	color;
	mlx_image_t	*mm;

	mm = game->minimap;
	if (game->config->map[y][x] == '1')
		color = 0xFFFFFFFF;
	else
		color = game->floor_color;
	i = 0;
	while (i < tile)
	{
		j = 0;
		while (j < tile)
		{
			mlx_put_pixel(mm,
				x * tile + j,
				y * tile + i,
				color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int			x;
	int			y;
	int			tile;
	mlx_image_t	*mm;

	tile = 5;
	mm = game->minimap;
	ft_memset(mm->pixels, 0, mm->width * mm->height * 4);
	y = 0;
	while (y < game->config->map_height)
	{
		x = 0;
		while (x < game->config->map_width)
		{
			draw_tile(game, tile, x, y);
			x++;
		}
		y++;
	}
	draw_player(game, mm, tile);
}
