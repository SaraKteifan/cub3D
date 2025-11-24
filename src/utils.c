/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:40:16 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/24 15:06:14 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    exit_str(char *msg)
{
    ft_putstr_fd(msg, 2);
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
