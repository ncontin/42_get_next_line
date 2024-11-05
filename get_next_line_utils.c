/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:55:06 by ncontin           #+#    #+#             */
/*   Updated: 2024/11/05 18:42:54 by ncontin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 2 malloc in total in here
int	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}
int	search_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup(char *str, int newline_pos)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(newline_pos + 1);
	if (dest == NULL)
		return (NULL);
	while (i <= newline_pos)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	tot_len;
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	tot_len = (ft_strlen(s1) + ft_strlen(s2));
	res = malloc(tot_len + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*conv;
	size_t	i;

	i = 0;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	conv = (char *)ptr;
	while (i < nmemb * size)
	{
		conv[i] = 0;
		i++;
	}
	return (ptr);
}
