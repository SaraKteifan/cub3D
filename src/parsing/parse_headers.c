/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:12:50 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/24 15:41:42 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_header_line(char *line, t_config *cfg);

int	parse_headers(int fd, t_config *cfg, char **line)
{
	while (*line)
	{
		if (is_line_empty(*line))
		{
			free(*line);
			*line = get_next_line(fd);
			continue;
		}
		if (parse_header_line(*line, cfg)) 
			break;
		*line = get_next_line(fd);
	}
	if (!cfg->north || !cfg->south || !cfg->west || !cfg->east
		|| cfg->floor[0] == -1 || cfg->ceiling[0] == -1)
	{
		ft_putstr_fd("Error\nMissing texture or color identifier\n", 2);
		exit(1);
	}
	return (0);
}

int parse_header_line(char *line, t_config *cfg)
{
    char *trimmed;
    int res;

    if (!line)
        return (-1);
    trimmed = trim_spaces(line);
    if (!trimmed) {
        free(line);
        return (-1);
    }
    res = handle_header_value(trimmed, cfg);
    free(trimmed);
	if (res == 0)
    	free(line);
    return res;
}

char	*parse_texture(char *line)
{
	char	*path;
	char	*trimmed;
	int		fd;

	path = ft_strdup(line + 2);
	if (!path)
		return (NULL);
	trimmed = trim_spaces(path);
	free(path);
	path = trimmed;
	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nInvalid texture path: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		free(path);
		return (NULL);
	}
	close(fd);
	return (path);
}

int	parse_color(char *line, int color[3])
{
	char	**parts;
	int		result;

	if (!line || !color)
		return (1);
	parts = ft_split(line + 2, ',');
	if (!parts)
		return (1);
	result = validate_color_parts(parts, color);
	free_split(parts);
	if (result)
		exit(1);
	return (0);
}