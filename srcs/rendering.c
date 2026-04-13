#include "../inc/cub3d.h"

#define CEILING_COLOR 0xB0E0E6
#define FLOOR_COLOR 0xF5DEB3 
#define MINIMAP_TILE_SIZE 15
#define MINIMAP_X 10           
#define MINIMAP_Y 560          

// test map
int test_map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

void put_pixel(char *data, int line_length, int x, int y, int color)
{
    int offset;
    char *pixel;

    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) // check if x, y is on scren
        return;
    offset = (y * line_length) + (x * 4);
    pixel = data + offset;
    *(int *)pixel = color;
}

void clear_image(char *data, int line_length, int start_y, int end_y, int color)
{
    int x;
    int y;

    y = start_y;
    while (y < end_y && y < SCREEN_HEIGHT)
    {
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            put_pixel(data, line_length, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_scene(char *data, int line_length)
{
    int midpoint;

    midpoint = SCREEN_HEIGHT / 2;
    clear_image(data, line_length, 0, midpoint, CEILING_COLOR);
    clear_image(data, line_length, midpoint, SCREEN_HEIGHT, FLOOR_COLOR);
}

void draw_minimap(char *data, int line_length)
{
    int map_x;
    int map_y;
    int pixel_x;
    int pixel_y;
    int tx;
    int ty;
    int color;

    map_y = 0;
    while (map_y < 10)
    {
        map_x = 0;
        while (map_x < 10)
        {
            ty = 0;
            while (ty < MINIMAP_TILE_SIZE)
            {
                tx = 0;
                while (tx < MINIMAP_TILE_SIZE)
                {
                    pixel_x = MINIMAP_X + (map_x * MINIMAP_TILE_SIZE) + tx;
                    pixel_y = MINIMAP_Y + (map_y * MINIMAP_TILE_SIZE) + ty;
                    if (test_map[map_y][map_x])
                        color = 0x000000;
                    else
                        color = 0xFFFFFF;
                    put_pixel(data, line_length, pixel_x, pixel_y, color);
                    tx++;
                }
                ty++;
            }
            map_x++;
        }
        map_y++;
    }
    // draw player on map to do
}

int rendering(t_game *game)
{
    draw_scene(game->image.data, game->image.line_length);
    draw_minimap(game->image.data, game->image.line_length);
    mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
    return (0);
}