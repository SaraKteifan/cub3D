/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:53:49 by skteifan          #+#    #+#             */
/*   Updated: 2025/11/23 21:53:49 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	get_longest_row(char **map)
// {
// 	int	i;
// 	int	longest;

// 	i = 0;
// 	longest = ft_strlen(map[0]);
// 	while (map[i])
// 	{
// 		if (ft_strlen(map[i]) > longest)
// 			longest = ft_strlen(map[i]);
// 		i++;
// 	}
// 	return (longest);
// }

// void	map_padding(t_game *game, char **map)
// {
// 	int	longest;

// 	longest = get_longest_row(map);
// }

int	setup_game(t_game *game)
{
	// map_padding(game, game->config->map);
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (1);
	init_player(game->player);
	setup_player_from_map(game->config, game->player);
	if (init_mlx(game) != 0)
		return (1);
	game->ceiling_color = rgb_to_uint32(game->config->ceiling);
	game->floor_color = rgb_to_uint32(game->config->floor);
	return (0);
}
