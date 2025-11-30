/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:40:16 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/29 15:50:27 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_str(char *msg)
{
	ft_putstr_fd(msg, 2);
	free_gnl_static();
	exit(1);
}

int is_line_empty(const char *line)
{
	int i;

	i = 0;
	if(!line)
		return (1);
	while(line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
char	*trim_spaces(char *str)
{
	int		start;
	int		end;
	char	*res;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t'))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n'))
		end--;
	res = ft_substr(str, start, end - start + 1);
	return (res);
}

void	replace_tabs_with_spaces(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}
