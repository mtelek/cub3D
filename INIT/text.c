#include "../Headers/cub3D.h"
#include <X11/Xlib.h>

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

int load_texture_and_reverse(void *mlx,  t_text *text, int y, int x)
{
	char	*temp_tex;
	int		byte;

	byte = 0;
	if (load_texture(mlx, text))
        return (1);
	temp_tex = malloc((size_t)text->line_l * (size_t)text->h);
	if (!temp_tex)
		return (free(temp_tex), 1);
	else
		while (y < text->h)
		{
			while (x >= 0)
			{
				while (byte < (text->bpp / 8))
				{
						temp_tex[y * text->line_l + (text->w - x - 1) * (text->bpp / 8) + byte]
					= text->addr[y * text->line_l + x * (text->bpp / 8) + byte];
					byte++;
				}
				byte = 0;
				x--;
			}
			y++;
			x = text->w - 1;
		}
	ft_memcpy(text->addr, temp_tex, text->line_l * text->h);
	free(temp_tex);
	return(0);
}

int load_textures(t_main *main) // do return
{
	if (
	load_texture(main->data->mlx_ptr, main->textures->no) ||
	load_texture_and_reverse(main->data->mlx_ptr, main->textures->so, 0, TEXT_SIZE - 1)
	|| load_texture(main->data->mlx_ptr, main->textures->ea)
	|| load_texture_and_reverse(main->data->mlx_ptr, main->textures->we, 0, TEXT_SIZE - 1))
		return (1);
	return (0);
}