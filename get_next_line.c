/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:21:31 by jwolfram          #+#    #+#             */
/*   Updated: 2024/05/08 14:33:28 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	free_fb(char **fbuffer)
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
	while (!ft_strchr(fbuffer, '\n') && bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
				return (free_fb(&fbuffer), free(buffer), NULL);
		fbuffer = ft_strjoin(fbuffer, buffer);
		if (!fbuffer)
			return (NULL);
	}
	free(buffer);

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
