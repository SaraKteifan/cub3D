/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:12:50 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/17 14:08:28 by ral-haba         ###   ########.fr       */
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
		free(*line);
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

static int	parse_header_line(char *line, t_config *cfg)
{
	char	*trimmed;
	int		result;

	if (!line)
		return (1);
	replace_tabs_with_spaces(line);
	trimmed = trim_spaces(line);
	if (!trimmed)
		return (1);
	if (is_duplicate_texture(trimmed, cfg) || is_duplicate_color(trimmed[0], cfg))
	{
		free(trimmed);
		exit(1);
	}
	result = handle_header_value(trimmed, cfg);
	free(trimmed);
	return (result);
}

char	*parse_texture(char *line)
{
	char	*path;
	int		fd;

	path = ft_strdup(line + 2);
	if (!path)
		return (NULL);
	path = trim_spaces(path);
	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0 || !is_xpm_file(path))
	{
		ft_putstr_fd("Error\nInvalid texture path or extention: ", 2);
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
int	is_xpm_file(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (!ft_strncmp(path + len - 4, ".xpm", 4))
		return (1);
	return (0);
}