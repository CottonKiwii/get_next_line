/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:27:22 by jwolfram          #+#    #+#             */
/*   Updated: 2024/05/08 14:29:37 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char	*str;
	size_t	fbuf_len;
	size_t	i;

	if (!s2)
		return (NULL);
	fbuf_len = 0;
	if (s1)
		fbuf_len = ft_strlen(s1);
	str = (char *)ft_calloc(fbuf_len + ft_strlen(s2) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i])
	{
		str[i + fbuf_len] = s2[i];
		i++;
	}
	return (str);
}
