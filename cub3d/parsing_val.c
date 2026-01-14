#include "cub3d.h"

int validate_map_info(t_game_data *data, char *map_line)
{
    int result;

    result = validate_texture(data, map_line);
    if (result != -1)
        return (result);
    if (strncmp(map_line, "F", 1) == 0 && map_line[1] == ' ')
        return (validate_color(data, map_line, 'F'));
    if (strncmp(map_line, "C", 1) == 0 && map_line[1] == ' ')
        return (validate_color(data, map_line, 'C'));
    if (map_line[0] == '\0')
        return (SUCCESS);
    if (first_phase_done(data) == SUCCESS)
        return (printf("first phase done check\n"), CONTINUE);
    return (printf("not done..\n"), FAILURE);
}

char *delete_newlines(char *map_line)
{   
    int i = 0;
    char *line;

    while (map_line[i] && map_line[i] != '\n' && map_line[i] != '\r')
        i++;
    line = strndup(map_line,i);
    return (line);
}
int is_valid_first_wall(char *map_line)
{
    int i = 0;

    while (map_line[i] == '\0')
        i++;
    while(map_line[i])
    {
        if (map_line[i] == '1')
            return (SUCCESS);
        i++;
    }
    return (FAILURE);
}

char **process_map_lines(t_game_data *data, int fd)
{
    char *temp;
    int status;

    data->map.line = get_next_line(fd);
    while (data->map.line)
    {   
        temp = data->map.line;
        data->map.line = delete_newlines(data->map.line);
        free(temp);
        status = validate_map_info(data, data->map.line);
        if (status == FAILURE)
            return (close(fd), free(data->map.line), NULL);
        if (data->first_phase_done && status == CONTINUE)
        {   
            if (is_valid_first_wall(data->map.line) == SUCCESS)
            {
                data->map.map = validate_map(data, fd);
                return (data->map.map);
            }
            return (close(fd), free(data->map.line), NULL);
        }
        free(data->map.line);
        data->map.line = get_next_line(fd);
    }
    return (close(fd), NULL);
}

char **parse_map(t_game_data *data, char *map)
{
    int fd;

    if (!map)
        return (NULL);
    fd = open(map, O_RDONLY);
    if (fd < 0)
        return (NULL);
    return (process_map_lines(data, fd));
}

