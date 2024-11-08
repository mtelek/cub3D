#include "../Headers/cub3D.h"

int load_texture(void *mlx, t_text *text)
{
    text->w = TEXT_SIZE;
    text->h = TEXT_SIZE;
    text->img = mlx_xpm_file_to_image(mlx, text->path, &text->w, &text->h);
    if (!text->img || text->w != TEXT_SIZE || text->h != TEXT_SIZE)
        return (printf(ERR_INV_TEXT_IMG), printf("%s\n", text->path), 1); // do free
    text->addr = mlx_get_data_addr(text->img, &text->bpp, &text->line_l, &text->endian);
	text->pix = (int *)text->addr;
	// printf("text->line_l: %d, text->w: %d, text->h: %d\n", text->line_l, text->w, text->h);
    return (0);
}

int load_textures(t_main *main) // do return
{
    if (
    load_texture(main->data->mlx_ptr, main->textures->no) ||
    load_texture(main->data->mlx_ptr, main->textures->so) ||
    load_texture(main->data->mlx_ptr, main->textures->we) ||
    load_texture(main->data->mlx_ptr, main->textures->ea))
		return (1);
    return (0);
}