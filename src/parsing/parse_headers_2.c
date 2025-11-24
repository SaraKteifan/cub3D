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

void	validate_and_assign_texture(char **dst, char *line, char *id)
{
	char *new_path;

	new_path = parse_texture(line);
	if (!new_path)
	{
		ft_putstr_fd("Error\nInvalid texture path: ", 2);
		ft_putstr_fd(id, 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}

	if (*dst)
		free(*dst);

	*dst = new_path;
}

int	handle_header_value(char *trimmed, t_config *cfg)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		validate_and_assign_texture(&cfg->north, trimmed, "NO");
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		validate_and_assign_texture(&cfg->south, trimmed, "SO");
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		validate_and_assign_texture(&cfg->west, trimmed, "WE");
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		validate_and_assign_texture(&cfg->east, trimmed, "EA");
	else if (trimmed[0] == 'F' && trimmed[1] == ' ')
		parse_color(trimmed, cfg->floor);
	else if (trimmed[0] == 'C' && trimmed[1] == ' ')
		parse_color(trimmed, cfg->ceiling);
	else
		return (1);
	return (0);
}
