/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 10:33:15 by ral-haba          #+#    #+#             */
/*   Updated: 2025/12/01 13:58:33 by ral-haba         ###   ########.fr       */
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
	{
		print_error_msg("Cannot open .cub file.");
		return (1);
	}
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
