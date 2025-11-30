/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:12:54 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/30 16:48:41 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**append_line(char **map, char *line)
{
	char	**new_map;
	int		len;
	int		i;

	len = 0;
	if (map)
		while (map[len])
			len++;
	new_map = malloc(sizeof(char *) * (len + 2));
	if (!new_map)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i++] = ft_strdup(line); // needs malloc fail handling
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

int	parse_map(int fd, t_config *cfg, char *line)
{
	int	flag = 0;
	while (line)
	{
		if (line && line[0] == '\n')
			flag = 1;
		else
		{
			if (flag == 1)
			{
				free(line);
				print_error_msg("Empty line in map.");
				return(1);
			}
			if (!is_map_line(line))
			{
				print_error_msg("Invalid character in map.");
				free(line);
				return (1);
			}
			cfg->map = append_line(cfg->map, line);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (validate_map(cfg))
	{
		print_error_msg("Invalid map: map is not closed or player unreachable");
		free_config_and_exit(cfg, NULL);
	}
	return (0);
}


