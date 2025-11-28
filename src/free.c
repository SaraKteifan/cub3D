/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:50:32 by ral-haba          #+#    #+#             */
/*   Updated: 2025/10/05 16:50:44 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *g_error_msg = NULL;

void	set_error_msg(const char *msg)
{
	if (g_error_msg)
		free(g_error_msg);
	if (!msg)
		g_error_msg = NULL;
	else
		g_error_msg = ft_strdup(msg);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
void free_config(t_config *cfg)
{
    if (cfg->north) free(cfg->north);
    if (cfg->south) free(cfg->south);
    if (cfg->west) free(cfg->west);
    if (cfg->east) free(cfg->east);

    if (cfg->map)
    {
        for (int i = 0; cfg->map[i]; i++)
            free(cfg->map[i]);
        free(cfg->map);
    }
}

void	free_all_and_exit(t_config *cfg, char *line)
{
	if (g_error_msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(g_error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	else
		ft_putstr_fd("Error\n", 2);
	if (line)
		free(line);
	free_config(cfg);
	free_gnl_static();
	if (g_error_msg)
	{
		free(g_error_msg);
		g_error_msg = NULL;
	}
	exit(1);
}
