/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:14:17 by ncontin           #+#    #+#             */
/*   Updated: 2024/10/30 13:42:33 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (buffer == NULL)
		return (NULL);
	line = NULL;
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
		if (search_newline(buffer))
		{
			ft_strdup(buffer);
		}
		else
		{
			// keep reading
		}
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("numbers.dict", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
}
