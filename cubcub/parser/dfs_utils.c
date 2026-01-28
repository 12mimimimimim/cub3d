/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:19:50 by vmorena           #+#    #+#             */
/*   Updated: 2025/09/18 19:19:50 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	locate_player(t_game_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while (data->map.map[y][x])
		{
			if (data->map.map[y][x] == 'N' || data->map.map[y][x] == 'E'
				|| data->map.map[y][x] == 'W' || data->map.map[y][x] == 'S')
			{
				data->player.x = x + 0.5;
				data->player.y = y + 0.5;
				data->player.direction = data->map.map[y][x];
				data->player.player_count++;
			}
			x++;
		}
		y++;
	}
	if (data->player.player_count != 1)
		return (ft_putstr_fd("Error\n[invalid player count]\n", 1), FAILURE);
	return (SUCCESS);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_walkable(char c)
{
	return (c == '0' || is_player(c));
}

int	is_out_of_bounds(t_game_data *data, int x, int y)
{
	if (y < 0 || y >= data->map.height)
		return (1);
	if (x < 0 || x >= data->map.width)
		return (1);
	return (0);
}

int	check_neighbor(t_game_data *data, int x, int y)
{
	char	c;

	if (is_out_of_bounds(data, x, y))
		return (FAILURE);
	c = data->map.map[y][x];
	if (c == '1')
		return (SUCCESS);
	return (CONTINUE);
}
