/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:12:54 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/29 13:02:14 by skteifan         ###   ########.fr       */
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
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i++] = ft_strdup(line);
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

int	parse_map(int fd, t_config *cfg, char *line)
{
	char	*tmp;

	while (line)
	{
		replace_tabs_with_spaces(line);
		if (is_line_empty(line))
		{
			/* skip leading empty lines before map starts */
			if (!cfg->map)
			{
				free(line);
				line = get_next_line(fd);
				continue ;
			}
			/* create a wall line with width = max existing line width or next non-empty line */
			int maxw = 0;
			for (int i = 0; cfg->map && cfg->map[i]; i++)
				if ((int)ft_strlen(cfg->map[i]) > maxw) maxw = ft_strlen(cfg->map[i]);
			if (maxw == 0)
			{
				tmp = get_next_line(fd);
				if (tmp)
				{
					maxw = ft_strlen(tmp);
					free(tmp);
				}
			}
			if (maxw <= 0) { free(line); line = get_next_line(fd); continue; }
			char *wall = malloc(maxw + 1);
			if (!wall) free_all_and_exit(cfg, line);
			for (int i = 0; i < maxw; ++i) wall[i] = '1';
			wall[maxw] = '\0';
			cfg->map = append_line(cfg->map, wall);
			free(wall);
			free(line);
			line = get_next_line(fd);
			continue;
		}
		cfg->map = append_line(cfg->map, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	line = NULL;
	if (validate_map(cfg))
	{
		set_error_msg("Invalid map: map is not closed or player unreachable");
		free_all_and_exit(cfg, NULL);
	}
	return (0);
}

