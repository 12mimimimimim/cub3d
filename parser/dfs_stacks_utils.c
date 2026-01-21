/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_stack_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:19:50 by vmorena          #+#    #+#             */
/*   Updated: 2025/09/18 19:19:50 by vmorena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	stack_push(t_stack *stack, int x, int y)
{
	t_stack_node	*new_node;

	new_node = malloc(sizeof(t_stack_node));
	if (!new_node)
		return (FAILURE);
	new_node->x = x;
	new_node->y = y;
	new_node->next = stack->top;
	stack->top = new_node;
	stack->size++;
	return (SUCCESS);
}

void	stack_init(t_stack *stack)
{
	stack->top = NULL;
	stack->size = 0;
}

int	stack_pop(t_stack *stack, int *x, int *y)
{
	t_stack_node	*temp;

	if (!stack->top)
		return (FAILURE);
	temp = stack->top;
	*x = temp->x;
	*y = temp->y;
	stack->top = temp->next;
	free(temp);
	stack->size--;
	return (SUCCESS);
}

int	stack_is_empty(t_stack *stack)
{
	//printf("stack is not empty\n");
	return (stack->top == NULL);
}

void	stack_clear(t_stack *stack)
{
	int	x;
	int	y;

	while (!stack_is_empty(stack))
		stack_pop(stack, &x, &y);
}
