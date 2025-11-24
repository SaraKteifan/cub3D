/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:12:54 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/24 16:09:34 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static char **append_line(char **map, char *line)
{
    char    **new_map;
    int     len;
    int     i;

    len = 0;
    if (map)
        while (map[len])
            len++;
    new_map = malloc(sizeof(char *) * (len + 2));
    if (!new_map)
        return (NULL);
    i = 0;
    while (i < len)
    {
        new_map[i] = map[i];
        i++;
    }
    new_map[i++] = ft_strdup(line);
    new_map[i] = NULL;
    free(map);
    return (new_map);
}
int	parse_map(int fd, t_config *cfg, char *line)
{
	while (line && !is_line_empty(line))
	{
		replace_tabs_with_spaces(line);
		cfg->map = append_line(cfg->map, line);
        // if (line)
		    free(line);
		line = get_next_line(fd);
	}
    // if(line)
	free(line);
    line = NULL;
	if (validate_map(cfg))
		exit_str("Error\nInvalid map\n");
	return (0);
}

