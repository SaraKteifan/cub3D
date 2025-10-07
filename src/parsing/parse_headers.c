/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:12:50 by ral-haba          #+#    #+#             */
/*   Updated: 2025/10/07 13:16:24 by ral-haba         ###   ########.fr       */
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
	if (ft_strncmp(line, "NO ", 3) == 0)
		cfg->north = parse_texture(line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		cfg->south = parse_texture(line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		cfg->west = parse_texture(line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		cfg->east = parse_texture(line);
	else if (line[0] == 'F' && line[1] == ' ')
	{
		if (parse_color(line, cfg->floor))
			return (1);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		if (parse_color(line, cfg->ceiling))
			return (1);
	}
	else
		return (1);
	return (0);
}

static char	*parse_texture(char *line)
{
	int		fd;
	int		len;
	char	*path;

	if (!line)
		return (NULL);
	path = ft_strdup(line + 3);
	if (!path)
		return (NULL);
	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' '))
		path[--len] = '\0';
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