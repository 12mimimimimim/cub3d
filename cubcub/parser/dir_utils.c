/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:19:50 by vmorena           #+#    #+#             */
/*   Updated: 2025/09/18 19:19:50 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_directions(int directions[4][2])
{
	directions[0][0] = 1;
	directions[0][1] = 0;
	directions[1][0] = -1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = 1;
	directions[3][0] = 0;
	directions[3][1] = -1;
}

int	process_single_neighbor(t_dfs_context *ctx, int dir_x, int dir_y)
{
	int	new_x;
	int	new_y;
	int	check;

	new_x = ctx->x + dir_x;
	new_y = ctx->y + dir_y;
	check = check_neighbor(ctx->data, new_x, new_y);
	if (check == FAILURE)
	{
		ft_putstr_fd("Error\n[hole in the wall spotted!]\n", 2);
		return (FAILURE);
	}
	if (check == CONTINUE)
	{
		if (stack_push(ctx->stack, new_x, new_y) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	process_neighbors(t_dfs_context *ctx)
{
	int	directions[4][2];
	int	i;

	init_directions(directions);
	i = 0;
	while (i < 4)
	{
		if (process_single_neighbor(ctx, directions[i][0],
			directions[i][1]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
