/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmorena <vmorena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 19:19:50 by vmorena           #+#    #+#             */
/*   Updated: 2025/09/18 19:19:50 by vmorena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	validate_color(t_game_data *data, char *map_line, char type)
{
	char	**rgb_values;
	t_rgb	*color;
	int		*set_flag;

	if (type == 'F')
	{
		color = &data->floor;
		set_flag = &data->floor_set;
	}
	else
	{
		color = &data->ceiling;
		set_flag = &data->ceiling_set;
	}
	rgb_values = rgb_init(map_line, type);
	if (validate_rgb(rgb_values[0], &color->r) == FAILURE
		|| validate_rgb(rgb_values[1], &color->g) == FAILURE
		|| validate_rgb(rgb_values[2], &color->b) == FAILURE)
	{
		free_2d_array(rgb_values);
		return (ft_putstr_fd("invalid rgb input\n", 2), FAILURE);
	}
	free_2d_array(rgb_values);
	*set_flag = 1;
	return (SUCCESS);
}

int validate_texture(t_game_data *data, char *map_line)
{
    t_texture_table textures[] = {
        {"NO", &data->texture.north_texture, 2},
        {"SO", &data->texture.south_texture, 2},
        {"WE", &data->texture.west_texture, 2},
        {"EA", &data->texture.east_texture, 2},
        {NULL, NULL, 0}
    };
    int i;

    i = 0;
    while (textures[i].key)
    {
        if (ft_strncmp(map_line, textures[i].key, textures[i].key_len) == 0 
            && map_line[textures[i].key_len] == ' ')
        {
            if (*textures[i].target)
                return (ft_putstr_fd("[ERROR] duplicate texture spotted\n",2), 0);
            *textures[i].target = ft_strdup(find_texture_path(map_line));
            return (SUCCESS);
        }
        i++;
    }
    return (-1);
} 