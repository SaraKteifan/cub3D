/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:12:50 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/30 15:39:46 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_header_value(char *trimmed, t_config *cfg)
{
	int	ret;

	ret = 1;
	if (ft_strncmp(trimmed, "NO", 2) == 0 && trimmed[2] == ' ')
		ret = validate_and_assign_texture(&cfg->north, trimmed);
	else if (ft_strncmp(trimmed, "SO", 2) == 0 && trimmed[2] == ' ')
		ret = validate_and_assign_texture(&cfg->south, trimmed);
	else if (ft_strncmp(trimmed, "WE", 2) == 0 && trimmed[2] == ' ')
		ret = validate_and_assign_texture(&cfg->west, trimmed);
	else if (ft_strncmp(trimmed, "EA", 2) == 0 && trimmed[2] == ' ')
		ret = validate_and_assign_texture(&cfg->east, trimmed);
	else if (ft_strncmp(trimmed, "F", 1) == 0 && trimmed[1] == ' ')
		ret = parse_color(trimmed, cfg->floor, cfg);
	else if (ft_strncmp(trimmed, "C", 1) == 0 && trimmed[1] == ' ')
		ret = parse_color(trimmed, cfg->ceiling, cfg);
	return (ret);
}

int	parse_header_line(char *line, t_config *cfg)
{
	char	*trimmed;
	int		res;

	// if (!line)
	// 	return (1);
	trimmed = trim_spaces(line);
	if (!trimmed)
	{
		print_error_msg("Malloc failed.");
		return (1);
	}
	res = handle_header_value(trimmed, cfg);
	free(trimmed);
	return (res);
}

int	parse_headers(int fd, t_config *cfg, char **line)
{
	char	*tmp;

	while (*line)
	{
		if (is_line_empty(*line))
		{
			free(*line);
			*line = get_next_line(fd);
			continue ;
		}
		if (parse_header_line(*line, cfg) == 1)
			break ;
		tmp = get_next_line(fd);
		free(*line);
		*line = tmp;
	}
	if (!cfg->north || !cfg->south || !cfg->west || !cfg->east
		|| cfg->floor[0] == -1 || cfg->ceiling[0] == -1)
	{
		print_error_msg("Incomplete header information or invalid data.");
		return (1);
	}
	return (0);
}
