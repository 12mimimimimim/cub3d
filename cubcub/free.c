/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:19:50 by vmorena           #+#    #+#             */
/*   Updated: 2025/09/18 19:19:50 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_game_data *data)
{
	if (data->north.image.img)
		mlx_destroy_image(data->mlx, data->north.image.img);
	if (data->south.image.img)
		mlx_destroy_image(data->mlx, data->south.image.img);
	if (data->east.image.img)
		mlx_destroy_image(data->mlx, data->east.image.img);
	if (data->west.image.img)
		mlx_destroy_image(data->mlx, data->west.image.img);
	if (data->texture.north_texture)
		free(data->texture.north_texture);
	if (data->texture.south_texture)
		free(data->texture.south_texture);
	if (data->texture.west_texture)
		free(data->texture.west_texture);
	if (data->texture.east_texture)
		free(data->texture.east_texture);
}

void	free_2d_array(char **string)
{
	int	i;

	i = 0;
	if (!string || !string[0])
		return ;
	while (string[i])
	{
		free(string[i]);
		i++;
	}
	free(string);
}
