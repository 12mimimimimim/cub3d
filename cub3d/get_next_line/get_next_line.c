/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:23:45 by vmorena           #+#    #+#             */
/*   Updated: 2025/05/08 21:23:45 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char			*src;
	unsigned char	tmp;

	tmp = (unsigned char)c;
	src = (char *)s;
	while (*src)
	{
		if ((unsigned char)*src == tmp)
			return (src);
		src++;
	}
	if (tmp == 0)
		return (src);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
	{
		return (NULL);
	}
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	return (result);
}

char	*free_and_return_null(char **storage, void *memory)
{
	if (*storage)
	{
		free(*storage);
		*storage = NULL;
	}
	free(memory);
	return (NULL);
}

char	*combined_buffer(int fd, char **static_string)
{
	int		bytes_read;
	char	*joined_line;
	char	*buf;

	buf = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(*static_string, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free_and_return_null(static_string, buf));
		buf[bytes_read] = '\0';
		if (bytes_read > 0)
		{
			joined_line = ft_strjoin((*static_string), buf);
			if (!joined_line)
				return (free_and_return_null(static_string, buf));
			free((*static_string));
			(*static_string) = joined_line;
		}
	}
	free(buf);
	return ((*static_string));
}

char	*extract_line_and_update_ss(char *read_line, char **static_string)
{
	int		i;
	char	*extracted_line;

	i = 0;
	while (read_line[i] && read_line[i] != '\n')
		i++;
	if (read_line[i] == '\n')
	{
		read_line[i] = '\0';
		extracted_line = ft_strdup_with_newline(read_line);
		*static_string = ft_strdup(&read_line[i + 1]);
		free(read_line);
	}
	else
	{
		extracted_line = ft_strdup(read_line);
		free(*static_string);
		*static_string = NULL;
	}
	return (extracted_line);
}

char	*get_next_line(int fd)
{
	static char	*static_string = NULL;
	char		*read_line;
	char		*extracted_line;

	if (!static_string)
	{
		static_string = malloc((1) * sizeof(char));
		if (!static_string)
			return (NULL);
		static_string[0] = '\0';
	}
	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	read_line = combined_buffer(fd, &static_string);
	if (!read_line || read_line[0] == '\0')
	{
		if (static_string)
			free(static_string);
		static_string = NULL;
		return (NULL);
	}
	extracted_line = extract_line_and_update_ss(read_line, &static_string);
	return (extracted_line);
}