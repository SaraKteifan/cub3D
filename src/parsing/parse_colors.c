/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:09:16 by ral-haba          #+#    #+#             */
/*   Updated: 2025/12/01 11:44:53 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_color_parts(char **parts, int color[3])
{
	int	i;

	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
		return (1);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_rgb_value(parts[i]))
			return (1);
		color[i] = ft_atoi(parts[i]);
		i++;
	}
	return (0);
}

int	is_duplicate_color(char id, t_config *cfg)
{
	if ((id == 'F' && cfg->floor[0] != -1)
		|| (id == 'C' && cfg->ceiling[0] != -1))
		return (1);
	return (0);
}

static int	check_comma_char(char c, int *last_was_comma, int *commas)
{
	if (c == ',')
	{
		if (*last_was_comma)
			return (0);
		(*commas)++;
		*last_was_comma = 1;
		return (1);
	}
	if (c >= '0' && c <= '9')
	{
		*last_was_comma = 0;
		return (1);
	}
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	valid_color_commas(char *s)
{
	int	i;
	int	commas;
	int	last_was_comma;

	i = 0;
	commas = 0;
	last_was_comma = 0;
	while (s[i])
	{
		if (!check_comma_char(s[i], &last_was_comma, &commas))
			return (0);
		i++;
	}
	if (last_was_comma)
		return (0);
	if (commas != 2)
		return (0);
	return (1);
}

int	parse_color(char *line, int color[3], t_config *cfg)
{
	char	**parts;
	char	*raw;
	int		result;

	if (is_duplicate_color(line[0], cfg))
		return (1);
	raw = line + 1;
	while (*raw == ' ' || *raw == '\t')
		raw++;
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
