#include "cub3d.h"

char	*parse_texture(char *line)
{
	char	*path;
	char	*trimmed;
	int		fd;
	char	*err;

	path = ft_strdup(line + 2);
	if (!path)
		return (NULL);
	trimmed = trim_spaces(path);
	free(path);
	if (!trimmed)
		return (NULL);
	fd = open(trimmed, O_RDONLY);
	if (fd < 0)
	{
		err = ft_strjoin("Invalid texture path: ", trimmed);
		set_error_msg(err);
		free(err);
		free(trimmed);
		return (NULL);
	}
	close(fd);
	return (trimmed);
}
