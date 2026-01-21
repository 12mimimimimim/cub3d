/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:19:50 by vmorena           #+#    #+#             */
/*   Updated: 2025/09/18 19:19:50 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_tlen;

	if (!s)
		return (NULL);
	s_tlen = ft_strlen(s);
	if (start >= s_tlen)
		return (ft_strdup(""));
	if (len > s_tlen - start)
		len = s_tlen - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*find_texture_path(char *map_line)
{
	int	i;

	i = 0;
	while (map_line[i] && map_line[i] != ' ' && map_line[i] != '\t')
		i++;
	while (map_line[i] && (map_line[i] == ' ' || map_line[i] == '\t'))
		i++;
	return (&map_line[i]);
}

char	**rgb_init(char *map_line, char c)
{
	char	*skip_the_character;
	char	**rgb_contents;
	int		i;

	i = 0;
	while (map_line[i] && map_line[i] == c)
		i++;
	skip_the_character = ft_substr(map_line, i,
			ft_strlen(map_line) - i);
	rgb_contents = ft_split(skip_the_character, ',');
	free(skip_the_character);
	return (rgb_contents);
}

int	validate_rgb(char *str, unsigned char *result)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (ft_strlen(str) > 4)
		return (ft_putstr_fd("bigger than 4\n", 2), FAILURE);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ft_putstr_fd("[ERROR] invalid character in rgb SPOTTED!!\n",2), FAILURE);
		i++;
	}
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num > 255)
			return (ft_putstr_fd("[ERROR] rgb range overflow/underflow\n",2), FAILURE);
		i++;
	}
	*result = (unsigned char)num;
	return (SUCCESS);
}

int	first_phase_done(t_game_data *data)
{
	if (data->texture.north_texture
		&& data->texture.west_texture
		&& data->texture.south_texture
		&& data->texture.east_texture
		&& data->ceiling_set
		&& data->floor_set)
		return (data->first_phase_done = 1, SUCCESS);
	return (FAILURE);
}
