/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:14:17 by ncontin           #+#    #+#             */
/*   Updated: 2024/11/15 12:53:17 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	clean_mem(char **buffer, char **stash)
{
	free(*buffer);
	*buffer = NULL;
	free(*stash);
	*stash = NULL;
}
int	extract_line(char **stash, char **line)
{
	char	*temp;
	int		nl_pos;

	nl_pos = search_newline(*stash);
	// if found extract the line until newlinepos
	if (nl_pos >= 0)
	{
		*line = ft_substr(*stash, 0, nl_pos + 1);
		temp = ft_substr(*stash, nl_pos + 1, ft_strlen(*stash) - nl_pos - 1);
		free(*stash);
		*stash = temp;
		return (1);
	}
	return (0);
}
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	int			bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		clean_mem(&buffer, &stash);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			clean_mem(&buffer, &stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (extract_line(&stash, &line))
			break ;
		// check EOF
		if (bytes_read == 0)
		{
			// check if string exists and is not empty
			if (stash && stash[0] != 0)
				line = ft_strdup(stash);
			else
				line = NULL;
			free(stash);
			stash = NULL;
		}
	}
	free(buffer);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		count;

// 	fd = open("empty.txt", O_RDONLY);
// 	count = 0;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		count++;
// 		printf("[%d]%s", count, line);
// 		free(line);
// 	}
// 	close(fd);
// }
