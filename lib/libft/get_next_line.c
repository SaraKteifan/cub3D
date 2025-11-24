/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:54:41 by ral-haba          #+#    #+#             */
/*   Updated: 2025/11/24 15:59:34 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_fd(int fd, char *line)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr_gnl(line, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		buffer[bytes] = '\0';
		line = ft_strjoin_gnl(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*set_line(char *line)
{
	char	*current_line;
	int		i;

	i = 0;
	if (!line[0])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	current_line = malloc(sizeof(char) * i + 1);
	if (!current_line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		current_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		current_line[i++] = '\n';
	current_line[i] = '\0';
	return (current_line);
}

char	*save_remain(char *line)
{
	char	*remain;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	remain = malloc(sizeof(char) * (ft_strlen_gnl(line) - i + 1));
	if (!remain)
	{
		free(line);
		return (NULL);
	}
	i++;
	while (line[i])
		remain[j++] = line[i++];
	remain[j] = '\0';
	free(line);
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*final;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	final = 0;
	line = read_fd(fd, line);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	final = set_line(line);
	line = save_remain(line);
	return (final);
}
