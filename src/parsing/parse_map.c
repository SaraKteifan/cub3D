/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:12:54 by ral-haba          #+#    #+#             */
/*   Updated: 2025/12/01 12:00:25 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_rows(char **map)
{
	int	len;

	len = 0;
	if (map)
		while (map[len])
			len++;
	return (len);
}

static char	**append_line(char **map, char *line)
{
	char	**new_map;
	int		len;
	int		i;

	len = count_map_rows(map);
	new_map = malloc(sizeof(char *) * (len + 2));
	if (!new_map)
	{
		free(map);
		return (NULL);
	}
	i = -1;
	while (++i < len)
		new_map[i] = map[i];
	new_map[i] = ft_strdup(line);
	if (!new_map[i])
	{
		free(map);
		return (NULL);
	}
	new_map[++i] = NULL;
	free(map);
	return (new_map);
}

static int	handle_map_line(t_config *cfg, char *line, int *flag)
{
	if (line[0] == '\n')
	{
		*flag = 1;
		return (0);
	}
	if (*flag == 1)
	{
		print_error_msg("Empty line in map.");
		return (1);
	}
	if (!is_map_line(line))
	{
		print_error_msg("Invalid character in map.");
		return (1);
	}
	cfg->map = append_line(cfg->map, line);
	return (0);
}

int	parse_map(int fd, t_config *cfg, char *line)
{
	int	flag;

	flag = 0;
	while (line)
	{
		if (handle_map_line(cfg, line, &flag))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (validate_map(cfg))
	{
		print_error_msg("Invalid map.");
		free_config_and_exit(cfg, NULL);
	}
	return (0);
}
