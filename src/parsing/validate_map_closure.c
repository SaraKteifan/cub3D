/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_closure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 22:51:14 by skteifan          #+#    #+#             */
/*   Updated: 2026/01/03 22:51:14 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	flood_fill(char **map, int x, int y)
{
	static int	dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	static int	dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int			i;

	if (y < 0 || x < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		return (1);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	map[y][x] = 'V';
	i = 0;
	while (i < 8)
	{
		if (flood_fill(map, x + dx[i], y + dy[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	is_valid_surround(char c)
{
	if (c != '0' && c != '1'
		&& c != 'N' && c != 'S'
		&& c != 'W' && c != 'E')
		return (0);
	return (1);
}

static int	check_surroundings(char **map, int x, int y)
{
	if (x == 0 || !map[y][x + 1])
		return (1);
	if (y == 0 || !map[y + 1])
		return (1);
	if (ft_strlen(map[y - 1]) < (size_t)(x + 2)
		|| ft_strlen(map[y + 1]) < (size_t)(x + 2))
		return (1);
	if (!is_valid_surround(map[y][x - 1])
		|| !is_valid_surround(map[y][x + 1])
		|| !is_valid_surround(map[y - 1][x - 1])
		|| !is_valid_surround(map[y - 1][x])
		|| !is_valid_surround(map[y - 1][x + 1])
		|| !is_valid_surround(map[y + 1][x - 1])
		|| !is_valid_surround(map[y + 1][x])
		|| !is_valid_surround(map[y + 1][x + 1]))
		return (1);
	return (0);
}

static int	is_map_open(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (check_surroundings(map, x, y))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map_closure(char **map, int px, int py)
{
	if (flood_fill(map, px, py))
		return (1);
	if (is_map_open(map))
		return (1);
	return (0);
}
