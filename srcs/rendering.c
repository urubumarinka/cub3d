#include "../inc/cub3d.h"

// Draw ceiling and floor background to buffer
void draw_scene_to_buffer(t_game *game)
{
    int x = 0;
    uint32_t floor_color = (game->map.text.flr_r << 16) | (game->map.text.flr_g << 8) | game->map.text.flr_b;
    uint32_t ceiling_color = (game->map.text.ceil_r << 16) | (game->map.text.ceil_g << 8) | game->map.text.ceil_b;
    while (x < SCREEN_WIDTH)
    {
        int y = 0;
        while (y < SCREEN_HEIGHT / 2)
        {
            game->buffer[y * SCREEN_WIDTH + x] = ceiling_color;
            y++;
        }
        y = SCREEN_HEIGHT / 2;
        while (y < SCREEN_HEIGHT)
        {
            game->buffer[y * SCREEN_WIDTH + x] = floor_color;
            y++;
        }
        x++;
    }
}

// draw a single pixel at coordinates x, y on the screen
void put_pixel(t_image *image, int x, int y, int color)
{
    int offset;  // where to write pixel
    char *pixel; // address of pixel
    // check if pixel is outside screen
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;
    offset = (y * image->line_length) + (x * 4);
    pixel = image->data + offset;
    *(int *)pixel = color; // write color there
}

// Draw buffer to screen image pixel by pixel
void draw_buffer_to_screen(t_image *image, uint32_t *buffer)
{
    int y = 0;
    while (y < SCREEN_HEIGHT)
    {
        int x = 0;
        while (x < SCREEN_WIDTH)
        {
            put_pixel(image, x, y, buffer[y * SCREEN_WIDTH + x]);
            x++;
        }
        y++;
    }
}

int rendering(t_game *game)
{
    int col;

    // draw ceiling/floor
    draw_scene_to_buffer(game);
    // Cast rays for each column and fill buffer with wall textures
    col = 0;
    while (col < SCREEN_WIDTH)
    {
        draw_wall_stripe(game, col);
        col++;
    }
    // Transfer buffer pixels to MLX image
    draw_buffer_to_screen(&game->image, game->buffer);

    // Draw minimap on top
    //draw_minimap(&game->image, game);
    // Display image on screen
    mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
    // clean pixels from current frame before drawing next frame
    memset(game->buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
    return (0);
}