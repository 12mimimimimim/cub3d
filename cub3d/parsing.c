#include "cub3d.h"
// the goal of this file is to fetch data from the map and initialize it's info 
// accordingly to it's rightful struct to prep it for execution


// the goal of this function is to read from the map
// validate errors
// and create a functioning struct with a properly initialized variable


// line by line check with the use of getnextline
// closer inspection for tracking NO, SO, WE, EEA and the colors

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_tlen;

	if (!s)
		return (NULL);
	s_tlen = ft_strlen(s);
	if (start >= s_tlen)
		return (ft_strdup(""));
	if (len > s_tlen - start)
		len = s_tlen - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char *find_texture_path(char *map_line)
{
    int i = 0;

    while(map_line[i] && map_line[i] != ' ' && map_line[i] != '\t')
    {
        i++;
    }
    while(map_line[i] && (map_line[i] == ' ' || map_line[i] == '\t'))
    {   
        i++;
    }
    return (&map_line[i]);
}

char **rgb_init(char *map_line, char c)
{
    char *skip_the_character;
    char **rgb_contents;

    int i = 0;

    while(map_line[i] && map_line[i] == c)
    {   
        i++;
    }
    skip_the_character = ft_substr(map_line, i, ft_strlen(map_line) - i);
    rgb_contents = ft_split(skip_the_character,',');
   free(skip_the_character);

   return (rgb_contents);
}

// check for invalid characters
// check for 
int validate_rgb(char *str,unsigned char *result)
{
    int i = 0;
    int num = 0;
    if (strlen(str) > 4)
        return (printf("bigger than 4\n"),FAILURE);
    while(str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (printf("[ERROR] invalid character in rgb SPOTTED!!\n"),(FAILURE));
        i++;
    }
    i = 0;
    while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num > 255)
			return (printf("rgb range overflow/underflow\n"),FAILURE);
		i++;
	}
    *result = (unsigned char)num;
    return (SUCCESS);
}
int  first_phase_done(t_game_data *data)
{   
    if (data->texture.north_texture && data->texture.west_texture && data->texture.south_texture
        && data->texture.east_texture && data->ceiling_set && data->floor_set)
      {
         data->first_phase_done = 1;
         return (SUCCESS);
      }
    return (FAILURE); 
}


