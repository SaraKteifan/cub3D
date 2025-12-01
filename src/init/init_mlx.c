/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:49:57 by skteifan          #+#    #+#             */
/*   Updated: 2025/12/01 11:39:59 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_frame(t_game *game)
{
	game->frame = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->frame)
	{
		print_error_msg((char *)mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(game->mlx, game->frame, 0, 0) == -1)
	{
		print_error_msg((char *)mlx_strerror(mlx_errno));
		return (1);
	}
	return (0);
}

int	init_textures(t_game *game)
{
	game->textures[NORTH] = mlx_load_png(game->config->north);
	if (!game->textures[NORTH])
	{
		print_error_msg("Failed to load texture NORTH.");
		return (1);
	}
	game->textures[SOUTH] = mlx_load_png(game->config->south);
	if (!game->textures[SOUTH])
	{
		print_error_msg("Failed to load texture SOUTH.");
		return (1);
	}
	game->textures[WEST] = mlx_load_png(game->config->west);
	if (!game->textures[WEST])
	{
		print_error_msg("Failed to load texture WEST.");
		return (1);
	}
	game->textures[EAST] = mlx_load_png(game->config->east);
	if (!game->textures[EAST])
	{
		print_error_msg("Failed to load texture EAST.");
		return (1);
	}
	return (0);
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!game->mlx)
	{
		print_error_msg((char *)mlx_strerror(mlx_errno));
		return (1);
	}
	if (init_frame(game) != 0)
	{
		clean_mlx_resources(game);
		return (1);
	}
	if (init_textures(game) != 0)
	{
		clean_mlx_resources(game);
		return (1);
	}
	mlx_loop_hook(game->mlx, &key_hook, game);
	return (0);
}
