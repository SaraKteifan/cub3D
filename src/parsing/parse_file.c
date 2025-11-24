/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 10:33:15 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/24 16:11:53 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static  void check_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("ERROR\nInvalid extension\n", 2);
		exit(1);
	}
}

int parse_file(char *filename, t_config *cfg)
{
    int fd;
    char    *line;
    int     status;

    if(!filename || !cfg)
        return (-1);    
    check_extension(filename);
    fd = open(filename, O_RDONLY);
    if(fd < 0)
        return(-1);
    init_config(cfg);
    line = get_next_line(fd);
    if(!line)
    {
        printf("line is null\n");
        return(-1);
    }
    status = parse_headers(fd, cfg, &line);
    if (status == 0)
        status = parse_map(fd, cfg, line);
    else if (line)
        free(line);
    close(fd);
    return (status);
}
