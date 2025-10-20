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

static void	find_player_pos(char **map, int *px, int *py)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSEW", map[y][x]))
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

static int	flood_fill(char **map, int x, int y)
{
	int	dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int	dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int	i;

	if (y < 0 || x < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		return (1);
	if (map[y][x] == ' ' || map[y][x] == '1' || map[y][x] == 'V')
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
	copy = duplicate_map(cfg->map);
	if (!copy)
		return (1);
	find_player_pos(copy, &px, &py);
	result = flood_fill(copy, px, py);
	free_split(copy);
	return (result);
}
