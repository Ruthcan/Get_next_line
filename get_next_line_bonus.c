/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcanchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:11:38 by rcanchan          #+#    #+#             */
/*   Updated: 2024/11/05 16:12:07 by rcanchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	if (line[i] == 0)
		return (NULL);
	store_lines = ft_substr(line, i + 1, ft_strlen(line) - i);
	line[i + 1] = 0;
	return (store_lines);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*store_lines[MAX_FD];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(store_lines[fd]);
		store_lines[fd] = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_lines(fd, store_lines[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	store_lines[fd] = extrac_line(line);
	return (line);
}

/*int main() {
    int fd1 = open("hola.txt", O_RDONLY);
    int fd2 = open("otro.txt", O_RDONLY); 
    
    if (fd1 < 0 || fd2 < 0) {
        perror("Error opening files");
        return 1;
    }
    char *line1 = get_next_line(fd1);
    char *line2 = get_next_line(fd2);
	int	i = 50;
    while (i > 0) 
	{
        if (line1) {
            printf("FD1: %s", line1);
            free(line1);
        }
        if (line2) {
            printf("FD2: %s", line2);
            free(line2);
        }
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		i--;
    }
    close(fd1);
    close(fd2);
    return 0;
}*/
