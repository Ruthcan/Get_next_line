/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcanchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:00:35 by rcanchan          #+#    #+#             */
/*   Updated: 2024/10/18 14:05:26 by rcanchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_lines(int fd, char *store_lines, char *buffer)
{
	ssize_t	number_bytes;
	char	*temporal_store;

	number_bytes = 1;
	while (number_bytes > 0)
	{
		number_bytes = read(fd, buffer, BUFFER_SIZE);
		if (number_bytes == -1)
		{
			free(store_lines);
			return (NULL);
		}
		else if (number_bytes == 0)
			break ;
		buffer[number_bytes] = 0;
		if (!store_lines)
			store_lines = ft_strdup("");
		temporal_store = store_lines;
		store_lines = ft_strjoin(temporal_store, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (store_lines);
}

static char	*extrac_line(char *line)
{
	char	*store_lines;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	store_lines = ft_substr(line, i + 1, ft_strlen(line) - i);
	line[i + 1] = 0;
	return (store_lines);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*store_lines;
	char			*line;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(store_lines);
		free(buffer);
		store_lines = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = read_lines(fd, store_lines, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	store_lines = extrac_line(line);
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("hola.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
} */