/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:50:32 by ral-haba          #+#    #+#             */
/*   Updated: 2025/12/01 11:39:42 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_config(t_config *cfg)
{
	int	i;

	if (cfg->north)
		free(cfg->north);
	if (cfg->south)
		free(cfg->south);
	if (cfg->west)
		free(cfg->west);
	if (cfg->east)
		free(cfg->east);
	i = 0;
	if (cfg->map)
	{
		while (cfg->map[i])
		{
			free(cfg->map[i]);
			i++;
		}
		free(cfg->map);
	}
	free(cfg);
}

void	clean_mlx_resources(t_game *game)
{
	if (game->frame)
		mlx_delete_image(game->mlx, game->frame);
	if (game->textures[NORTH])
		mlx_delete_texture(game->textures[NORTH]);
	if (game->textures[SOUTH])
		mlx_delete_texture(game->textures[SOUTH]);
	if (game->textures[EAST])
		mlx_delete_texture(game->textures[EAST]);
	if (game->textures[WEST])
		mlx_delete_texture(game->textures[WEST]);
	mlx_terminate(game->mlx);
}

void	free_config_and_exit(t_config *cfg, char *line)
{
	if (line)
		free(line);
	free_config(cfg);
	free_gnl_static();
	exit(1);
}

void	free_all_and_exit(t_game *game)
{
	free_config(game->config);
	free_gnl_static();
	free(game->player);
	clean_mlx_resources(game);
	exit(1);
}
