// #include "cub3d.h"
// #include <math.h>

// #define SCREEN_WIDTH 1920
// #define SCREEN_HEIGHT 1080
// #define FOV 60
// #define MOVE_SPEED 0.15
// #define ROT_SPEED 0.08


// // Put pixel in image buffer (faster than mlx_pixel_put)
// void my_mlx_pixel_put(t_image *img, int x, int y, int color)
// {
//     char *dst;

//     if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
//         return;
//     dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

// // Initialize player direction vectors based on starting direction
// void init_player_direction(t_game_data *data)
// {
//     if (data->player.direction == 'N')
//     {
//         data->raycast.dir_x = 0;
//         data->raycast.dir_y = -1;
//         data->raycast.plane_x = 0.66;
//         data->raycast.plane_y = 0;
//     }
//     else if (data->player.direction == 'S')
//     {
//         data->raycast.dir_x = 0;
//         data->raycast.dir_y = 1;
//         data->raycast.plane_x = -0.66;
//         data->raycast.plane_y = 0;
//     }
//     else if (data->player.direction == 'E')
//     {
//         data->raycast.dir_x = 1;
//         data->raycast.dir_y = 0;
//         data->raycast.plane_x = 0;
//         data->raycast.plane_y = 0.66;
//     }
//     else if (data->player.direction == 'W')
//     {
//         data->raycast.dir_x = -1;
//         data->raycast.dir_y = 0;
//         data->raycast.plane_x = 0;
//         data->raycast.plane_y = -0.66;
//     }
//     data->raycast.player_x = data->player.x + 0.5;
//     data->raycast.player_y = data->player.y + 0.5;
// }

// // Calculate ray direction and initial DDA values
// void init_ray(t_game_data *data, int x)
// {
//     data->raycast.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
//     data->raycast.ray_dir_x = data->raycast.dir_x + data->raycast.plane_x * data->raycast.camera_x;
//     data->raycast.ray_dir_y = data->raycast.dir_y + data->raycast.plane_y * data->raycast.camera_x;
    
//     data->raycast.map_x = (int)data->raycast.player_x;
//     data->raycast.map_y = (int)data->raycast.player_y;
    
//     if (data->raycast.ray_dir_x == 0)
//         data->raycast.delta_dist_x = 1e30;
//     else
//         data->raycast.delta_dist_x = fabs(1 / data->raycast.ray_dir_x);
    
//     if (data->raycast.ray_dir_y == 0)
//         data->raycast.delta_dist_y = 1e30;
//     else
//         data->raycast.delta_dist_y = fabs(1 / data->raycast.ray_dir_y);
// }

// // Setup DDA algorithm
// void setup_dda(t_game_data *data)
// {
//     if (data->raycast.ray_dir_x < 0)
//     {
//         data->raycast.step_x = -1;
//         data->raycast.side_dist_x = (data->raycast.player_x - data->raycast.map_x) * data->raycast.delta_dist_x;
//     }
//     else
//     {
//         data->raycast.step_x = 1;
//         data->raycast.side_dist_x = (data->raycast.map_x + 1.0 - data->raycast.player_x) * data->raycast.delta_dist_x;
//     }
    
//     if (data->raycast.ray_dir_y < 0)
//     {
//         data->raycast.step_y = -1;
//         data->raycast.side_dist_y = (data->raycast.player_y - data->raycast.map_y) * data->raycast.delta_dist_y;
//     }
//     else
//     {
//         data->raycast.step_y = 1;
//         data->raycast.side_dist_y = (data->raycast.map_y + 1.0 - data->raycast.player_y) * data->raycast.delta_dist_y;
//     }
// }

// // Perform DDA to find wall hit
// void perform_dda(t_game_data *data)
// {
//     int hit = 0;
    
//     while (hit == 0)
//     {
//         if (data->raycast.side_dist_x < data->raycast.side_dist_y)
//         {
//             data->raycast.side_dist_x += data->raycast.delta_dist_x;
//             data->raycast.map_x += data->raycast.step_x;
//             data->raycast.side = 0;
//         }
//         else
//         {
//             data->raycast.side_dist_y += data->raycast.delta_dist_y;
//             data->raycast.map_y += data->raycast.step_y;
//             data->raycast.side = 1;
//         }
        
//         if (data->raycast.map_x < 0 || data->raycast.map_y < 0 || 
//             data->raycast.map_y >= data->map.height || 
//             data->raycast.map_x >= data->map.width)
//             hit = 1;
//         else if (data->map.map[data->raycast.map_y][data->raycast.map_x] == '1')
//             hit = 1;
//     }
// }

// // Calculate wall distance and height
// void calculate_wall_distance(t_game_data *data)
// {
//     if (data->raycast.side == 0)
//         data->raycast.perp_wall_dist = (data->raycast.map_x - data->raycast.player_x + 
//                                         (1 - data->raycast.step_x) / 2) / data->raycast.ray_dir_x;
//     else
//         data->raycast.perp_wall_dist = (data->raycast.map_y - data->raycast.player_y + 
//                                         (1 - data->raycast.step_y) / 2) / data->raycast.ray_dir_y;
    
//     data->raycast.line_height = (int)(SCREEN_HEIGHT / data->raycast.perp_wall_dist);
//     data->raycast.draw_start = -data->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
//     if (data->raycast.draw_start < 0)
//         data->raycast.draw_start = 0;
    
//     data->raycast.draw_end = data->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
//     if (data->raycast.draw_end >= SCREEN_HEIGHT)
//         data->raycast.draw_end = SCREEN_HEIGHT - 1;
// }

// // Get wall color based on direction
// int get_wall_color(t_game_data *data)
// {
//     int color;
    
//     if (data->raycast.side == 0)
//     {
//         if (data->raycast.step_x > 0)
//             color = 0xFF0000; // East - Red
//         else
//             color = 0x0000FF; // West - Blue
//     }
//     else
//     {
//         if (data->raycast.step_y > 0)
//             color = 0x00FF00; // South - Green
//         else
//             color = 0xFFFF00; // North - Yellow
//     }
    
//     // Darken side walls for depth effect
//     if (data->raycast.side == 1)
//         color = color / 2;
    
//     return color;
// }

// // Draw vertical line for current ray
// void draw_vertical_line(t_game_data *data, t_image *img, int x)
// {
//     int y;
//     int ceiling_color = (data->ceiling.r << 16) | (data->ceiling.g << 8) | data->ceiling.b;
//     int floor_color = (data->floor.r << 16) | (data->floor.g << 8) | data->floor.b;
//     int wall_color = get_wall_color(data);
    
//     // Draw ceiling
//     y = 0;
//     while (y < data->raycast.draw_start)
//     {
//         my_mlx_pixel_put(img, x, y, ceiling_color);
//         y++;
//     }
    
//     // Draw wall
//     while (y < data->raycast.draw_end)
//     {
//         my_mlx_pixel_put(img, x, y, wall_color);
//         y++;
//     }
    
//     // Draw floor
//     while (y < SCREEN_HEIGHT)
//     {
//         my_mlx_pixel_put(img, x, y, floor_color);
//         y++;
//     }
// }

// // Main raycasting function
// void raycast(t_game_data *data, t_image *img)
// {
//     int x;
    
//     x = 0;
//     while (x < SCREEN_WIDTH)
//     {
//         init_ray(data, x);
//         setup_dda(data);
//         perform_dda(data);
//         calculate_wall_distance(data);
//         draw_vertical_line(data, img, x);
//         x++;
//     }
// }

// // Handle player movement
// void move_player(t_game_data *data, double move_x, double move_y)
// {
//     double new_x = data->raycast.player_x + move_x;
//     double new_y = data->raycast.player_y + move_y;
    
//     // Check collision with some margin
//     int check_x = (int)new_x;
//     int check_y = (int)new_y;
    
//     if (check_y >= 0 && check_y < data->map.height && 
//         check_x >= 0 && check_x < data->map.width)
//     {
//         if (data->map.map[check_y][check_x] != '1' &&
//             data->map.map[check_y][check_x] != 'X')
//         {
//             data->raycast.player_x = new_x;
//             data->raycast.player_y = new_y;
//         }
//     }
// }

// // Rotate player view
// void rotate_player(t_game_data *data, double angle)
// {
//     double old_dir_x = data->raycast.dir_x;
//     double old_plane_x = data->raycast.plane_x;
    
//     data->raycast.dir_x = data->raycast.dir_x * cos(angle) - data->raycast.dir_y * sin(angle);
//     data->raycast.dir_y = old_dir_x * sin(angle) + data->raycast.dir_y * cos(angle);
    
//     data->raycast.plane_x = data->raycast.plane_x * cos(angle) - data->raycast.plane_y * sin(angle);
//     data->raycast.plane_y = old_plane_x * sin(angle) + data->raycast.plane_y * cos(angle);
// }

// // Render frame
// void render_frame(t_game_data *data, t_image *img)
// {
//     raycast(data, img);
//     mlx_put_image_to_window(data->mlx, data->win, img->img, 0, 0);
// }

// // Key press handler
// int key_press(int keycode, t_game_data *data)
// {
//     t_image *img = (t_image *)data->raycast.img_data;
//     int moved = 0;
    
//     // ESC key (Linux: 65307, macOS: 53)
//     if (keycode == 65307 || keycode == 53)
//     {
//         mlx_destroy_window(data->mlx, data->win);
//         exit(0);
//     }
    
//     // W key - move forward (Linux: 119, macOS: 13)
//     if (keycode == 119 || keycode == 13)
//     {
//         move_player(data, data->raycast.dir_x * MOVE_SPEED, data->raycast.dir_y * MOVE_SPEED);
//         moved = 1;
//     }
    
//     // S key - move backward (Linux: 115, macOS: 1)
//     if (keycode == 115 || keycode == 1)
//     {
//         move_player(data, -data->raycast.dir_x * MOVE_SPEED, -data->raycast.dir_y * MOVE_SPEED);
//         moved = 1;
//     }
    
//     // A key - strafe left (Linux: 97, macOS: 0)
//     if (keycode == 100 || keycode == 0)
//     {
//         move_player(data, -data->raycast.dir_y * MOVE_SPEED, data->raycast.dir_x * MOVE_SPEED);
//         moved = 1;
//     }
    
//     // D key - strafe right (Linux: 100, macOS: 2)
//     if (keycode == 97 || keycode == 2)
//     {
//         move_player(data, data->raycast.dir_y * MOVE_SPEED, -data->raycast.dir_x * MOVE_SPEED);
//         moved = 1;
//     }
    
//     // Left arrow - rotate left (Linux: 65361, macOS: 123)
//     if (keycode == 65363 || keycode == 123)
//     {
//         rotate_player(data, ROT_SPEED);
//         moved = 1;
//     }
    
//     // Right arrow - rotate right (Linux: 65363, macOS: 124)
//     if (keycode == 65361 || keycode == 124)
//     {
//         rotate_player(data, -ROT_SPEED);
//         moved = 1;
//     }
    
//     // Only redraw if something changed
//     if (moved)
//     {
//         render_frame(data, img);
//     }
    
//     return (0);
// }

// // Close window handler
// int close_window(t_game_data *data)
// {
//     mlx_destroy_window(data->mlx, data->win);
//     exit(0);
//     return (0);
// }

// // Initialize and start the game
// void start_game(t_game_data *data)
// {
//     t_image img;
    
//     data->mlx = mlx_init();
//     if (!data->mlx)
//     {
//         printf("[ERROR] Failed to initialize MLX\n");
//         return;
//     }
    
//     data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
//     if (!data->win)
//     {
//         printf("[ERROR] Failed to create window\n");
//         return;
//     }
    
//     // Create image buffer for faster rendering
//     img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    
//     // Store image in raycast struct for access in key handler
//     data->raycast.img_data = &img;
    
//     init_player_direction(data);
    
//     // Initial render
//     render_frame(data, &img);
    
//     // Setup hooks
//     mlx_hook(data->win, 2, 1L<<0, key_press, data);
//     mlx_hook(data->win, 17, 0, close_window, data);
    
//     mlx_loop(data->mlx);
// }