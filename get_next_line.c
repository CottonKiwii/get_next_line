/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CottonKiwii <julia.wolfram@gmx.at>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:21:31 by jwolfram          #+#    #+#             */
/*   Updated: 2024/05/15 16:04:54 by CottonKiwii      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_fb(char **fbuff)
{
	free(*fbuff);
	*fbuff = NULL;
}

char	*ft_get_line(char *fbuff)
{
	char	*line;
	char	*newline;
	size_t	len;

	if (!fbuff)
		return (NULL);
	newline = ft_strchr(fbuff, '\n');
	if (!newline)
	{
		line = ft_substr(fbuff, 0, ft_strlen(fbuff));
		if (!line || !ft_strlen(line))
			return (free(line), NULL);
		return (line);
	}
	len = newline - fbuff + 1;
	line = ft_substr(fbuff, 0, len);
	return (line);
}

char	*ft_next_line(char *buffer, char *fbuff)
{
	char	*next;
	char	*newline;
	size_t	newline_index;
	size_t	line_len;

	if (!buffer || !fbuff)
		return (free_fb(&fbuff), NULL);
	newline = ft_strchr(fbuff, '\n');
	if (!newline || ft_strlen(newline) == 1)
		return (free_fb(&fbuff), NULL);
	newline_index = newline - fbuff;
	line_len = ft_strlen(fbuff);
	next = ft_substr(fbuff, newline_index + 1, line_len - newline_index - 1);
	return (free_fb(&fbuff), next);
}

char	*get_next_line(int fd)
{
	static char	*fbuff;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free_fb(&fbuff), NULL);
	bytes_read = 1;
	while (!ft_strchr(fbuff, '\n') && bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_fb(&fbuff), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		fbuff = ft_strjoin(fbuff, buffer);
	}
	free(buffer);
	buffer = ft_get_line(fbuff);
	fbuff = ft_next_line(buffer, fbuff);
	return (buffer);
}
