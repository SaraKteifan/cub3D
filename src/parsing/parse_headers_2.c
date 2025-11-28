/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:12:55 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/24 13:30:29 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* validate_and_assign_texture: returns 0 on success, 1 on error */
int validate_and_assign_texture(char **dst, char *line)
{
	char *path;

	path = parse_texture(line);
	if (!path)
		return (1); /* parse_texture sets error message */
	if (*dst)
	{
		free(path);
		set_error_msg("Duplicate texture identifier");
		return (1);
	}
	*dst = path;
	return (0);
}

int handle_header_value(char *trimmed, t_config *cfg)
{
	if (ft_strncmp(trimmed, "NO", 2) == 0 && trimmed[2] == ' ')
		return (validate_and_assign_texture(&cfg->north, trimmed));
	else if (ft_strncmp(trimmed, "SO", 2) == 0 && trimmed[2] == ' ')
		return (validate_and_assign_texture(&cfg->south, trimmed));
	else if (ft_strncmp(trimmed, "WE", 2) == 0 && trimmed[2] == ' ')
		return (validate_and_assign_texture(&cfg->west, trimmed));
	else if (ft_strncmp(trimmed, "EA", 2) == 0 && trimmed[2] == ' ')
		return (validate_and_assign_texture(&cfg->east, trimmed));
	else if (ft_strncmp(trimmed, "F", 1) == 0 && trimmed[1] == ' ')
		return (parse_color(trimmed, cfg->floor));
	else if (ft_strncmp(trimmed, "C", 1) == 0 && trimmed[1] == ' ')
		return (parse_color(trimmed, cfg->ceiling));
	return (1);
}
