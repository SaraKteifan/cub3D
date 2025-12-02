/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:59:22 by skteifan          #+#    #+#             */
/*   Updated: 2025/12/02 15:24:36 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_game *game, int dir)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x + game->player->dir_x * MOVE_SPEED * dir;
	new_y = game->player->y + game->player->dir_y * MOVE_SPEED * dir;
	if (game->config->map[(int)new_y][(int)game->player->x] != '1')
		game->player->y = new_y;
	if (game->config->map[(int)game->player->y][(int)new_x] != '1')
		game->player->x = new_x;
	render_frame(game);
}

void	player_strafe(t_game *game, int dir)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x + game->player->plane_x * MOVE_SPEED * dir;
	new_y = game->player->y + game->player->plane_y * MOVE_SPEED * dir;
	if (game->config->map[(int)new_y][(int)game->player->x] != '1')
		game->player->y = new_y;
	if (game->config->map[(int)game->player->y][(int)new_x] != '1')
		game->player->x = new_x;
	render_frame(game);
}

void	player_rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = ROT_SPEED * angle;
	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(rot)
		- game->player->dir_y * sin(rot);
	game->player->dir_y = old_dir_x
		* sin(rot) + game->player->dir_y * cos(rot);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(rot)
		- game->player->plane_y * sin(rot);
	game->player->plane_y = old_plane_x * sin(rot)
		+ game->player->plane_y * cos(rot);
	render_frame(game);
}

void	close_hook(void *param)
{
	t_game	*game;

	game = param;
	free_all_and_exit(game);
}

void	key_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		player_move(game, +1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		player_move(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		player_strafe(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		player_strafe(game, +1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player_rotate(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player_rotate(game, +1);
}
