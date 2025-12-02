/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ral-haba <ral-haba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:58:48 by skteifan          #+#    #+#             */
/*   Updated: 2025/12/01 14:34:32 by ral-haba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_all(char *s1, char *s2)
{
	free (s1);
	free (s2);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*joined;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	joined = malloc(i + j + 1);
	if (!joined)
	{
		free_all(s1, s2);
		return (NULL);
	}
	k = -1;
	while (++k < i)
		joined[k] = s1[k];
	k--;
	while (++k < i + j)
		joined[k] = s2[k - i];
	joined[i + j] = '\0';
	free(s1);
	return (joined);
}

char	*initialize_repo(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

int	check_no_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}
