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

int parse_headers(int fd, t_config *cfg, char **line)
{
	char	*tmp;

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
		tmp = get_next_line(fd);
		free(*line);
		*line = tmp;
	}
	if (!cfg->north || !cfg->south || !cfg->west || !cfg->east
		|| cfg->floor[0] == -1 || cfg->ceiling[0] == -1)
	{
		set_error_msg("Incomplete header information");
		return (1);
	}
	return (0);
}

int parse_header_line(char *line, t_config *cfg)
{
	char	*trimmed;
	int		res;

	if (!line)
		return (-1);
	trimmed = trim_spaces(line);
	if (!trimmed)
		return (-1);
	res = handle_header_value(trimmed, cfg);
	free(trimmed);
	return (res);
}

int parse_color(char *line, int color[3])
{
	char	**parts;
	char	*raw;
	int		result;

	raw = line + 2;
	if (!valid_color_commas(raw))
		return (1);
	parts = ft_split(raw, ',');
	if (!parts)
		return (1);
	result = validate_color_parts(parts, color);
	if (result)
	{
		free_split(parts);
		return (1);
	}
	free_split(parts);
	return (0);
}
