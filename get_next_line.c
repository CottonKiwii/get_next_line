/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:21:31 by jwolfram          #+#    #+#             */
/*   Updated: 2024/05/10 18:18:38 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	free_fb(char **fbuff)
{
	free(*fbuff);
	*fbuff = NULL;
}

char	*ft_get_line(char *fbuff)
{
	char	*line;
	char	*newline;
	char	*temp;
	
	if (!fbuff)
		return (NULL);
	newline = ft_strchr(fbuff, '\n');
	line = ft_substr(fbuff, fbuff[0], (size_t)newline);
	return (line);
}

char	*ft_next_line(char *buffer, char *fbuff)
{
	char	*next;

	return (next);
}

char	*get_next_line(int fd)
{
	static char	*fbuff;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(fbuff, '\n') && bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
				return (free_fb(&fbuff), free(buffer), NULL);
		fbuff = ft_strjoin(fbuff, buffer);
		if (!fbuff)
			return (NULL);
	}
	free(buffer);
	buffer = ft_get_line(fbuff);
	fbuff = ft_next_line(buffer, fbuff);
	return (buffer);
}

/* MAIN FUNCTION */

#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("overview.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	/*while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s\n", line);
		free(line);
		line = NULL;
	}*/
	close(fd);
	return (0);	
}
