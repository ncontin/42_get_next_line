/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:14:17 by ncontin           #+#    #+#             */
/*   Updated: 2024/11/06 19:26:22 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	int			bytes_read;
	char		*temp;
	int			newline_pos;
	char		*buffer;
	static char	*stash = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	// Read and accumulate in stash until newline or EOF
	while (!stash || search_newline(stash) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup(buffer, bytes_read);
		else
		{
			temp = ft_strjoin(stash, buffer);
			free(stash);
			stash = temp;
		}
	}
	// Handle EOF or error
	if (!stash || bytes_read < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	// Extract line and update stash
	newline_pos = search_newline(stash);
	if (newline_pos >= 0)
	{
		line = ft_strdup(stash, newline_pos + 1);
		temp = ft_substr(stash, newline_pos + 1, ft_strlen(stash)
				- newline_pos);
		free(stash);
		stash = temp;
	}
	else
	{
		line = ft_strdup(stash, ft_strlen(stash));
		free(stash);
		stash = NULL;
	}
	return (line);
}

#include <stdio.h>

int	main(void)

{
	int fd;
	char *line;

	fd = open("numbers.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
