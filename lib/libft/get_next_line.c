/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:50:43 by skteifan          #+#    #+#             */
/*   Updated: 2025/12/01 14:33:44 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*delete_line(char *repo)
{
	char	*new_repo;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (repo[i] != '\0')
		i++;
	while (repo[j] != '\n' && repo[j] != '\0')
		j++;
	if (repo[j] == '\n')
		j++;
	new_repo = malloc(i - j + 1);
	if (!new_repo)
	{
		free(repo);
		return (NULL);
	}
	i = 0;
	while (repo[j] != '\0')
		new_repo[i++] = repo[j++];
	new_repo[i] = '\0';
	free (repo);
	return (new_repo);
}

char	*cut_the_line(char	*repo)
{
	char	*line;
	int		i;

	i = 0;
	while (repo[i] != '\n' && repo[i] != '\0')
		i++;
	if (repo[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
	{
		free(repo);
		repo = NULL;
		return (NULL);
	}
	i = 0;
	while (repo[i] != '\n' && repo[i] != '\0')
	{
		line[i] = repo[i];
		i++;
	}
	if (repo[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*reading_file(int fd, char *repo, char *buffer)
{
	ssize_t		bytes_read;

	bytes_read = 1;
	while (repo && check_no_nl(repo) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || (ft_strlen(repo) == 0 && bytes_read == 0))
		{
			free_all(repo, buffer);
			repo = NULL;
			return (NULL);
		}
		else if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			repo = ft_strjoin_gnl(repo, buffer);
		}
	}
	return (repo);
}

static char	*extract_line(char **repo)
{
	char	*line;

	line = cut_the_line(*repo);
	if (!line)
		return (NULL);
	*repo = delete_line(*repo);
	if (*repo && (*repo)[0] == '\0')
	{
		free(*repo);
		*repo = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*repo;
	char		*buffer;
	char		*line;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!repo)
		repo = initialize_repo();
	if (!buffer || !repo)
	{
		free_all(repo, buffer);
		repo = NULL;
		return (NULL);
	}
	repo = reading_file(fd, repo, buffer);
	if (!repo)
		return (NULL);
	free(buffer);
	line = extract_line(&repo);
	return (line);
}
