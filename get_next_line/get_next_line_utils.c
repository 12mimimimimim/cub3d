/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:23:41 by vmorena           #+#    #+#             */
/*   Updated: 2025/05/08 21:23:41 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*tmp_src;
	unsigned char		*tmp_dst;

	tmp_dst = (unsigned char *)dst;
	tmp_src = (const unsigned char *)src;
	if (!tmp_dst || !tmp_src)
	{
		return (NULL);
	}
	while (n--)
	{
		*tmp_dst++ = *tmp_src++;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*dst;
	size_t	i;

	dst = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup_with_newline(const char *src)
{
	size_t	len;
	char	*new_string;

	len = ft_strlen(src);
	new_string = malloc((len + 2) * sizeof(char));
	if (!new_string)
		return (NULL);
	ft_memcpy(new_string, src, len);
	new_string[len] = '\n';
	new_string[len + 1] = '\0';
	return (new_string);
}