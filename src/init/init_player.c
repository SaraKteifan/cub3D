/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:24:16 by skteifan          #+#    #+#             */
/*   Updated: 2025/11/23 21:24:16 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

char	set_player_start_position(char **map, t_player *player)
{
	char	pos;
	int		y;
	int		x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player_char(map[y][x]))
			{
				pos = map[y][x];
				player->x = x + 0.5;
				player->y = y + 0.5;
				map[y][x] = '0';
				return (pos);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	set_player_start_direction_vector(char pos, t_player *player)
{
	if (pos == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (pos == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (pos == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (pos == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
}

void	calculate_camera_plane(t_player *player)
{
	player->plane_x = -player->dir_y * FOV_FACTOR;
	player->plane_y = player->dir_x * FOV_FACTOR;
}

void	setup_player_from_map(t_config *config, t_player *player)
{
	char	pos;

	pos = set_player_start_position(config->map, player);
	set_player_start_direction_vector(pos, player);
	calculate_camera_plane(player);
}
