/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:19:50 by vmorena           #+#    #+#             */
/*   Updated: 2025/09/18 19:19:50 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	char_patrol(char c)
{
	if (ft_strchr("10NSWE ", c) == NULL)
		return (FAILURE);
	return (SUCCESS);
}

char	**update_map(char **map, char *line, int size)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = malloc(sizeof(char *) * (size + 1));
	if (!new_map)
		return (NULL);
	if (map)
	{
		while (i < size - 1)
		{
			new_map[i] = map[i];
			i++;
		}
	}
	new_map[i++] = line;
	new_map[i] = NULL;
	if (map)
		free(map);
	return (new_map);
}

int	process_map_line(t_game_data *data,
		char **cleaned_line, int *max_width)
{
	int	i;

	i = 0;
	*cleaned_line = delete_newlines(data->map.line);
	if ((*cleaned_line)[0] == '\0')
	{
		ft_putstr_fd("Error [hole spotted in the map!]\n", 2);
		free(*cleaned_line);
		return (FAILURE);
	}
	while ((*cleaned_line)[i])
	{
		if (char_patrol((*cleaned_line)[i]) == FAILURE)
		{
			ft_putstr_fd("Error [incorrect character spotted]\n", 2);
			free(*cleaned_line);
			return (FAILURE);
		}
		i++;
	}
	if (i > *max_width)
		*max_width = i;
	return (SUCCESS);
}

char	**validate_map(t_game_data *data, int fd)
{
	int		max_i;
	int		line_count;
	char	*original_line;
	char	*cleaned_line;

	max_i = 0;
	line_count = 0;
	while (data->map.line)
	{
		original_line = data->map.line;
		if (process_map_line(data,
				&cleaned_line, &max_i) == FAILURE)
			return (free_2d_array(data->map.map), free(original_line), NULL);
		line_count++;
		data->map.map = update_map(data->map.map,
				ft_strdup(cleaned_line), line_count);
		if (!data->map.map)
			return (free(original_line), free(cleaned_line), NULL);
		free(original_line);
		free(cleaned_line);
		data->map.line = get_next_line(fd);
	}
	data->map.height = line_count;
	data->map.width = max_i;
	return (data->map.map);
}
