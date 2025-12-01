/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:54:43 by skteifan          #+#    #+#             */
/*   Updated: 2025/09/10 00:54:43 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_game(t_game *game)
{
	free_all_and_exit(game);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		status;

	if (ac != 2)
	{
		print_error_msg("You must provide exactly one argument.");
		return (1);
	}
	init_game(&game);
	if (init_config(&game.config) != 0)
		return (1);
	status = parse_file(av[1], game.config);
	if (status != 0)
		free_config_and_exit(game.config, NULL);
	status = setup_game(&game);
	if (status != 0)
		free_all_and_exit(&game);
	status = render_frame(&game);
	mlx_close_hook(game.mlx, close_hook, &game);
	mlx_loop(game.mlx);
	free_all_and_exit(&game);
	return (0);
}
