/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:19:50 by vmorena           #+#    #+#             */
/*   Updated: 2025/09/18 19:19:50 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	dfs_iterate(t_dfs_context *ctx)
{
	int	result;

	while (!stack_is_empty(ctx->stack))
	{
		stack_pop(ctx->stack, &ctx->x, &ctx->y);
		if (ctx->visited[ctx->y][ctx->x] == 'V')
			continue ;
		ctx->visited[ctx->y][ctx->x] = 'V';
		result = process_neighbors(ctx);
		if (result == FAILURE)
		{
			stack_clear(ctx->stack);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	dfs(t_game_data *data, char **visited, int start_x, int start_y)
{
	t_stack			stack;
	t_dfs_context	ctx;

	stack_init(&stack);
	ctx.data = data;
	ctx.visited = visited;
	ctx.stack = &stack;
	if (stack_push(&stack, start_x, start_y) == FAILURE)
		return (FAILURE);
	return (dfs_iterate(&ctx));
}

char	**create_visited_map(t_game_data *data)
{
	char	**visited;
	int		i;

	i = 0;
	visited = malloc(sizeof(char *) * (data->map.height + 1));
	if (!visited)
		return (NULL);
	while (i < data->map.height)
	{
		visited[i] = ft_calloc(data->map.width + 1, sizeof(char));
		if (!visited[i])
		{
			free_2d_array(visited);
			return (NULL);
		}
		i++;
	}
	visited[i] = NULL;
	return (visited);
}

int	validate_map_with_dfs(t_game_data *data)
{
	char	**visited;
	int		result;

	if (locate_player(data) == FAILURE)
		return (FAILURE);
	visited = create_visited_map(data);
	if (!visited)
	{
		ft_putstr_fd("Error [allocation error in char **visited]\n", 2);
		return (FAILURE);
	}
	result = dfs(data, visited, data->player.x, data->player.y);
	free_2d_array(visited);
	if (result == SUCCESS)
		ft_putstr_fd("[MAP FULLY VALIDATED]\n", 1);
	else
		ft_putstr_fd("Error [MAP VALIDATED UNSUCCESFULLY]\n", 2);
	return (result);
}
