/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:12:50 by ral-haba          #+#    #+#             */
/*   Updated: 2025/10/29 13:19:16 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *parse_texture(char *line);
static int parse_color(char *line, int color[3]);
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
	return (0);
}
static int	parse_header_line(char *line, t_config *cfg)
{
	char	*trimmed;

	if (!line)
		return (1);
	replace_tabs_with_spaces(line);
	trimmed = trim_spaces(line);
	if (!trimmed)
		return (1);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		cfg->north = parse_texture(trimmed);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		cfg->south = parse_texture(trimmed);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		cfg->west = parse_texture(trimmed);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		cfg->east = parse_texture(trimmed);
	else if (trimmed[0] == 'F' && trimmed[1] == ' ')
		parse_color(trimmed, cfg->floor);
	else if (trimmed[0] == 'C' && trimmed[1] == ' ')
		parse_color(trimmed, cfg->ceiling);
	else
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}

static char	*parse_texture(char *line)
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
	if (fd < 0)
	{
		ft_putstr_fd("Error\nInvalid texture path: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		free(path);
		return (NULL);
	}
	close(fd);
	return (path);
}



static int parse_color(char *line, int color[3])
{
    char  **parts;
    int     i;
    int	    value;
    
    i = 0;
    if(!line || !color)
        return (1);
    parts = ft_split(line + 2, ',');
    if(!parts)
        return (1);
    if(!parts[0] || !parts[1] || !parts[2] || parts[3])
    {
        ft_putstr_fd("Error\nInvalid color format\n", 2);
        free_split(parts);
        return (1);
    }
    while (i < 3)
    {
    	value = ft_atoi(parts[i]);
    	if (value < 0 || value > 255)
    	{
    		ft_putstr_fd("Error\nColor out of range\n", 2);
    		free_split(parts);
    		return (1);
    	}
    	color[i++] = value;
    }
    free_split(parts);
    return (0);

}