/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 10:33:15 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/30 15:59:42 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
	{
		print_error_msg("Invalid extension.");
		return (1);
	}
	return (0);
}

int	parse_file(char *filename, t_config *cfg)
{
	int		fd;
	char	*line;

	if (check_extension(filename) != 0)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_str("Cannot open .cub file.");
	line = get_next_line(fd);
	if (parse_headers(fd, cfg, &line))
	{
		free(line);
		close(fd);
		return (1);
	}
	if (parse_map(fd, cfg, line))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
