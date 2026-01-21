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

int	process_neighbors(t_dfs_context *ctx)
{
	int	directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int	i;
	int	new_x;
	int	new_y;
	int	check;

	i = 0;
	while (i < 4)
	{
		new_x = ctx->x + directions[i][0];
		new_y = ctx->y + directions[i][1];
		check = check_neighbor(ctx->data, new_x, new_y);
		if (check == FAILURE)
			return (ft_putstr_fd("[ERROR] hole in the wall spotted!\n", 2), FAILURE);
		//printf("visitied value: %c \n",  ctx->visited[new_y][new_x]);
		if (check == CONTINUE)
		{	
			if (stack_push(ctx->stack, new_x, new_y) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
 void print_visited_map(char **v_map, int height, int width)
{
    int i = 0;
    
    printf("printing visited map:\n");
    while (i < height)
    {
        int j = 0;
        while (j < width)
        {
            printf("[%c]", v_map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

int	dfs_iterate(t_dfs_context *ctx)
{
	int	result;

	while (!stack_is_empty(ctx->stack))
	{
		stack_pop(ctx->stack, &ctx->x, &ctx->y);
		if (ctx->visited[ctx->y][ctx->x] == 'V')
		{
			//printf("enters here\n");
			continue ;
		}
		ctx->visited[ctx->y][ctx->x] = 'V';
		result = process_neighbors(ctx);
		if (result == FAILURE)
		{
			stack_clear(ctx->stack);
			return (FAILURE);
		}
		//printf("looping\n");
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

		visited[i] = calloc(data->map.width + 1, sizeof(char));
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
		return (ft_putstr_fd("[ALLOCATION ERROR] in char **visited\n", 2), FAILURE);
	result = dfs(data, visited, data->player.x, data->player.y);
	print_visited_map(visited, data->map.height, data->map.width);
	free_2d_array(visited);
	if (result == SUCCESS)
		ft_putstr_fd("[MAP FULLY VALIDATED]\n", 1);
	else
		ft_putstr_fd("[MAP VALIDATED UNSUCCESFULLY]\n", 1);
	return (result);
}
