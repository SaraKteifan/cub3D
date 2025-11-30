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

void cleanup_game(t_game *game)
{
	(void)game;
	free_all_and_exit(game);
	// clean_mlx_textures_and_img(game);

	// free map
	//free_map(game->config->map);

	// free config structs
	// free(game->config);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		status;

	if(ac != 2)
		print_error_msg("You must provide exactly one argument.");
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


	// printf("North: %s\n", game.config->north);
	// printf("South: %s\n", game.config->south);
	// printf("West: %s\n", game.config->west);
	// printf("East: %s\n", game.config->east);
	// printf("Floor: %d,%d,%d\n", game.config->floor[0], game.config->floor[1], game.config->floor[2]);
	// printf("Ceiling: %d,%d,%d\n", game.config->ceiling[0], game.config->ceiling[1], game.config->ceiling[2]);

	// for (int i = 0; game.config->map && game.config->map[i]; i++)
	// printf("%s", game.config->map[i]);

	// printf("\n");
	// for (int i = 0; game.config->map && game.config->map[i]; i++)
	// printf("%zu\n", ft_strlen(game.config->map[i]));

	return (0);
}
