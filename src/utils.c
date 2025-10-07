/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:40:16 by ral-haba          #+#    #+#             */
/*   Updated: 2025/10/07 13:11:18 by ral-haba         ###   ########.fr       */
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