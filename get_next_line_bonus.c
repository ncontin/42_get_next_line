/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:49:17 by ncontin           #+#    #+#             */
/*   Updated: 2024/11/18 15:35:41 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*clean_stash_buf(char **buffer, char **stash)
{
	free(*buffer);
	*buffer = NULL;
	free(*stash);
	*stash = NULL;
	return (NULL);
}

int	extract_line(char **stash, char **line)
{
	char	*temp;
	int		nl_pos;

	nl_pos = search_newline(*stash);
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

void	check_eof(int bytes_read, char **stash, char **line)
{
	if (bytes_read == 0)
	{
		if (*stash && **stash != 0)
			*line = ft_strdup(*stash);
		else
			*line = NULL;
		free(*stash);
		*stash = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buffer;
	char		*line;
	int			bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (clean_stash_buf(&buffer, &stash[fd]));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (clean_stash_buf(&buffer, &stash[fd]));
		buffer[bytes_read] = '\0';
		stash[fd] = ft_strjoin(stash[fd], buffer);
		if (extract_line(&stash[fd], &line))
			break ;
		check_eof(bytes_read, &stash[fd], &line);
	}
	free(buffer);
	return (line);
}
