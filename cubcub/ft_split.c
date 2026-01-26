/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:19:50 by vmorena           #+#    #+#             */
/*   Updated: 2025/09/18 19:19:50 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	i = 0;
	while (src[src_len])
	{
		src_len++;
	}
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

int	ss_counter(char const *s, char c)
{
	int	i;
	int	word_count;
	int	in_word;

	i = 0;
	word_count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == ' ')
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			word_count++;
		}
		i++;
	}
	return (word_count);
}

char	*get_c(char const *s, int *i, char c)
{
	int		j;
	char	*word;

	j = *i;
	while (s[j] && s[j] != c && s[j] != ' ')
		j++;
	word = malloc(j - *i + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + *i, j - *i + 1);
	*i = j;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		word_count;
	char	**result;

	i = 0;
	k = 0;
	word_count = ss_counter(s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c || s[i] == ' ')
			i++;
		else
		{
			result[k] = get_c(s, &i, c);
			if (!result[k])
				return (NULL);
			k++;
		}
	}
	result[k] = NULL;
	return (result);
}

void	free_split_result(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}
