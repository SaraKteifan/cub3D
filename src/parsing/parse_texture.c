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

char	*parse_texture(char *line)
{
	char	*path;
	char	*trimmed;
	int		fd;
	char	*err;

	path = ft_strdup(line + 2);
	if (!path)
		return (NULL);
	trimmed = trim_spaces(path);
	free(path);
	if (!trimmed)
		return (NULL);
	fd = open(trimmed, O_RDONLY);
	if (fd < 0)
	{
		err = ft_strjoin("Invalid texture path: ", trimmed);
		set_error_msg(err);
		free(err);
		free(trimmed);
		return (NULL);
	}
	close(fd);
	return (trimmed);
}

/* validate_and_assign_texture: returns 0 on success, 1 on error */
int	validate_and_assign_texture(char **dst, char *line)
{
	char	*path;

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
