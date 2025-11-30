/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:49:57 by skteifan          #+#    #+#             */
/*   Updated: 2025/11/23 22:49:57 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(t_game *game)
{
	game->textures[NORTH] = mlx_load_png(game->config->north);
	game->textures[SOUTH] = mlx_load_png(game->config->south);
	game->textures[WEST] = mlx_load_png(game->config->west);
	game->textures[EAST] = mlx_load_png(game->config->east);
	if (!game->textures[NORTH] || !game->textures[SOUTH]
		||!game->textures[WEST] || !game->textures[EAST])
	{
		ft_putstr_fd("Failed to load texture\n", 2);
		return (1);
	}
	return (0);
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!game->mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		return (1);
	}
	game->frame = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->frame)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		mlx_terminate(game->mlx);
		return (1);
	}
	mlx_image_to_window(game->mlx, game->frame, 0, 0);
	game->minimap = mlx_new_image(game->mlx, 150, 150);
	mlx_image_to_window(game->mlx, game->minimap, 10, 10);
	if (init_textures(game) != 0)
		return (1);
	mlx_loop_hook(game->mlx, &key_hook, game);
	return (0);
}
