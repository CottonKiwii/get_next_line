/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:21:31 by jwolfram          #+#    #+#             */
/*   Updated: 2024/05/07 17:57:25 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	amount;
	size_t	i;

	if (!nmemb || !size)
		return (malloc(0));
	amount = nmemb * size;
	if (nmemb != amount / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		((char *)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (!s[i] && (unsigned char)c)
		return (NULL);
	return (&((char *)s)[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strm;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	strm = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char *));
	if (!strm)
		return (NULL);
	str = strm;
	while (*s1)
	{
		*str = *s1;
		str++;
		s1++;
	}
	while (*s2)
	{
		*str = *s2;
		str++;
		s2++;
	}
	return (strm);
}

void	ft_free_buffer(char **fbuffer)
{
	free(*fbuffer);
	*fbuffer = NULL;
}

/* ACTUAL FILE */

char	*get_next_line(int fd)
{
	static char	*fbuffer;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	printf("1\n");
	while (!ft_strchr(fbuffer, '\n') && bytes_read)
	{
		printf("2\n");
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || bytes_read <= 0)
				return (ft_free_buffer(&fbuffer), free(buffer), NULL);
		printf("3\n");
		fbuffer = ft_strjoin(fbuffer, buffer);
		if (!fbuffer)
			return (NULL);
		printf("4\n");
		free(buffer);
	}
	return (buffer);
}

/* MAIN FUNCTION */

#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open("overview.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		printf("[%d]:%s\n", count, line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);	
}
