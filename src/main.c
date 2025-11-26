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

void free_config(t_config *cfg)
{
    if (cfg->north) free(cfg->north);
    if (cfg->south) free(cfg->south);
    if (cfg->west) free(cfg->west);
    if (cfg->east) free(cfg->east);

    if (cfg->map)
    {
        for (int i = 0; cfg->map[i]; i++)
            free(cfg->map[i]);
        free(cfg->map);
    }
}

int	main(int ac, char **av)
{
	t_config config;
	int		status;

	if(ac != 2)
		exit_str("Error\nYou have assign two argument\n");
	status = parse_file(av[1], &config);
	if (status != 0)
		exit_str("Error\nError while parsing the file\n");


	printf("North: %s\n", config.north);
	printf("South: %s\n", config.south);
	printf("West: %s\n", config.west);
	printf("East: %s\n", config.east);
	printf("Floor: %d,%d,%d\n", config.floor[0], config.floor[1], config.floor[2]);
	printf("Ceiling: %d,%d,%d\n", config.ceiling[0], config.ceiling[1], config.ceiling[2]);

	for (int i = 0; config.map && config.map[i]; i++)
    printf("%s", config.map[i]);

	free_config(&config);
	return (0);
}
