/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:19:50 by vmorena           #+#    #+#             */
/*   Updated: 2025/09/18 19:19:50 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*create_padded_line(char *original_line, int target_width)
{
	char	*padded_line;
	int		current_len;
	int		j;

	current_len = strlen(original_line);
	padded_line = malloc(sizeof(char) * (target_width + 1));
	if (!padded_line)
		return (NULL);
	j = 0;
	while (j < current_len)
	{
		if (original_line[j] == ' ')
			padded_line[j] = 'X';
		else
			padded_line[j] = original_line[j];
		j++;
	}
	while (j < target_width)
	{
		padded_line[j] = 'X';
		j++;
	}
	padded_line[j] = '\0';
	return (padded_line);
}

void	patch_map(t_game_data *data)
{
	char	**padded_map;
	int		i;

	i = 0;
	padded_map = malloc(sizeof(char *) * (data->map.height + 1));
	if (!padded_map)
		return ;
	while (i < data->map.height)
	{
		padded_map[i] = create_padded_line(
				data->map.map[i], data->map.width);
		if (!padded_map[i])
		{
			free_2d_array(padded_map);
			return ;
		}
		i++;
	}
	padded_map[i] = NULL;
	free_2d_array(data->map.map);
	data->map.map = padded_map;
}

int	main(int argc, char *argv[])
{
	t_game_data	data;

	data = (t_game_data){0};
	if (argc == 2)
	{
		if (!parse_map(&data, argv[1]))
			return (ft_putstr_fd("Error [Invalid map file]\n", 2),
				free_textures(&data), get_next_line(42), 1);
		patch_map(&data);
		if (validate_map_with_dfs(&data) == FAILURE)
		{
			free_2d_array(data.map.map);
			free_textures(&data);
			return (get_next_line(42), 1);
		}
		start_game(&data);
	}
	else
	{
		ft_putstr_fd("Error [usage ./cub3D <map path>\n]", 2);
		return (1);
	}
	return (0);
}
