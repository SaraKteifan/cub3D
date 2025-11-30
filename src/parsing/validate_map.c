/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:00:00 by ral-haba          #+#    #+#             */
/*   Updated: 2025/10/17 19:00:00 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_size(char **map)
{
	int	rows = 0;
	int	cols = 0;

	while (map[rows])
	{
		int len = ft_strlen(map[rows]);
		if (len > cols)
			cols = len;
		rows++;
	}
	if (rows < 3 || cols < 3)
		return (1);
	return (0);
}

static char	**duplicate_map(char **map)
{
	int		y;
	char	**copy;

	y = 0;
	while (map[y])
		y++;
	copy = malloc(sizeof(char *) * (y + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (map[y])
	{
		copy[y] = ft_strdup(map[y]);
		if (!copy[y])
			return (NULL);
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

static int	find_player_pos(char **map, int *px, int *py)
{
	int	y = 0;
	int	x;
	int	player_count = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSEW", map[y][x]))
			{
				*px = x;
				*py = y;
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (1);
	return (0);
}

static int	flood_fill(char **map, int x, int y)
{
	int	dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int	dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int	i;

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
int	validate_map(t_config *cfg)
{
	char	**copy;
	int		px;
	int		py;
	int		result;

	if (!cfg || !cfg->map)
		return (1);
	// if(only_map_chars(cfg->map))
	// 	return (1);
	copy = duplicate_map(cfg->map);
	if (!copy)
		return (1);
	if (check_map_size(cfg->map))
	{
		free_split(copy);
		return (1);
	}
	if (find_player_pos(copy, &px, &py))
	{
		free_split(copy);
		return (1);
	}
	result = flood_fill(copy, px, py);
	free_split(copy);
	return (result);
}

