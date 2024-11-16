/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:05:21 by ncontin           #+#    #+#             */
/*   Updated: 2024/11/16 12:23:08 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd);
void	check_eof(int bytes_read, char **stash, char **line);
int		extract_line(char **stash, char **line);
void	*clean_stash_buf(char **buffer, char **stash);

int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	fd = open("1char.txt", O_RDONLY);
	count = 0;
	line = get_next_line(1);
	while (line)
	{
		count++;
		printf("[%d]%s", count, line);
		free(line);
		line = get_next_line(1);
	}
	close(fd);
}
