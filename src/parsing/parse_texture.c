/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 22:36:24 by skteifan          #+#    #+#             */
/*   Updated: 2025/11/29 22:36:24 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_png(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".png", 4) != 0)
	{
		free(path);
		return (1);
	}
	return (0);
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
	if (!trimmed)
		return (NULL);
	if (is_png(trimmed))
		return (NULL);
	fd = open(trimmed, O_RDONLY);
	if (fd < 0)
	{
		free(trimmed);
		return (NULL);
	}
	close(fd);
	return (trimmed);
}

int	validate_and_assign_texture(char **dst, char *line)
{
	char	*path;

	path = parse_texture(line);
	if (!path)
		return (1);
	if (*dst)
	{
		free(path);
		return (1);
	}
	*dst = path;
	return (0);
}
