/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_headers_config.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:09:16 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/03 13:17:20 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_rgb_value(char *part)
{
	int	value;

	if (!ft_is_number(part))
		return (0);
	value = ft_atoi(part);
	if (value < 0 || value > 255)
		return (0);
	return (1);
}
int	validate_color_parts(char **parts, int color[3])
{
	int	i;

	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		ft_putstr_fd("Error\nInvalid color format (expected R,G,B)\n", 2);
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		if (!is_valid_rgb_value(parts[i]))
		{
			ft_putstr_fd("Error\nColor value must be between 0-255\n", 2);
			return (1);
		}
		color[i] = ft_atoi(parts[i]);
		i++;
	}
	return (0);
}
int	is_duplicate_texture(char *id, t_config *cfg)
{
	if ((ft_strncmp(id, "NO ", 3) == 0 && cfg->north)
		|| (ft_strncmp(id, "SO ", 3) == 0 && cfg->south)
		|| (ft_strncmp(id, "WE ", 3) == 0 && cfg->west)
		|| (ft_strncmp(id, "EA ", 3) == 0 && cfg->east))
	{
		ft_putstr_fd("Error\nDuplicate texture identifier\n", 2);
		return (1);
	}
	return (0);
}

int	is_duplicate_color(char id, t_config *cfg)
{
	if ((id == 'F' && cfg->floor[0] != -1)
		|| (id == 'C' && cfg->ceiling[0] != -1))
	{
		ft_putstr_fd("Error\nDuplicate color identifier\n", 2);
		return (1);
	}
	return (0);
}
int valid_color_commas(char *s)
{
    int i = 0;
    int commas = 0;
    int last_was_comma = 0;

    while (s[i])
    {
        if (s[i] == ',')
        {
            if (last_was_comma)  // consecutive commas → error
                return (0);
            commas++;
            last_was_comma = 1;
        }
        else if (s[i] >= '0' && s[i] <= '9')
            last_was_comma = 0;
        else if (s[i] != ' ' && s[i] != '\t')
            return (0);
        i++;
    }
    if (last_was_comma)   // ends with comma → error
        return (0);
    if (commas != 2)
        return (0);
    return (1);
}
