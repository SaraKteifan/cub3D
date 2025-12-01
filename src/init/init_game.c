/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:53:49 by skteifan          #+#    #+#             */
/*   Updated: 2025/12/01 11:00:38 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	setup_game(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		print_error_msg("Malloc failed.");
		return (1);
	}
	init_player(game->player);
	if (setup_player_from_map(game->config, game->player) != 0)
		return (1);
	if (init_mlx(game) != 0)
		return (1);
	game->ceiling_color = rgb_to_uint32(game->config->ceiling);
	game->floor_color = rgb_to_uint32(game->config->floor);
	return (0);
}
