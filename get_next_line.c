/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:14:17 by ncontin           #+#    #+#             */
/*   Updated: 2024/11/05 18:53:06 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			bytes_read;
	int			newline_pos;
	char		*temp;

	if (buffer == NULL)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (buffer == NULL)
			return (NULL);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	// read return -1 if an error occured, needs protection for that
	if (bytes_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	// read data until the end of the file
	while (bytes_read)
	{
		// search for the newline and store newline position
		newline_pos = search_newline(buffer);
		// if newline is valid
		if (newline_pos >= 0)
		{
			line = ft_strdup(buffer, newline_pos);
			break ;
		}
		else
		{
			temp = line;
			line = ft_strjoin(line, buffer);
			free(temp);
			bytes_read = read(fd, buffer, BUFFER_SIZE);
		}
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	fd = open("numbers.dict", O_RDONLY);
	line = get_next_line(fd);
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		printf("[%d]%s", count, line);
		free(line);
	}
	close(fd);
}
