/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:01:33 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/03 11:01:33 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		if (!(line[i] == '1' || line[i] == '0'
				|| line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W'
				|| line[i] == '\n' || line[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	print_config_errors(t_config *cfg)
{
	ft_putstr_fd("Error\n", 2);
	if (!cfg->north)
		ft_putstr_fd("Missing north texture.\n", 2);
	if (!cfg->south)
		ft_putstr_fd("Missing south texture.\n", 2);
	if (!cfg->west)
		ft_putstr_fd("Missing west texture.\n", 2);
	if (!cfg->east)
		ft_putstr_fd("Missing east texture.\n", 2);
	if (cfg->floor[0] == -1 || cfg->floor[1] == -1 || cfg->floor[2] == -1)
		ft_putstr_fd("Invalid floor color.\n", 2);
	if (cfg->ceiling[0] == -1 || cfg->ceiling[1] == -1 || cfg->ceiling[2] == -1)
		ft_putstr_fd("Invalid ceiling color.\n", 2);
}

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
