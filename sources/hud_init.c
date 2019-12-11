/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hud_init.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/23 18:13:15 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 18:51:41 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

int		get_text_colorhud(t_file *file, float x, float y, int last)
{
	float	test;
	int		y2;

	test = (int)((x / file->width) * MAP.hudsize);
	y2 = (int)((y / last) * MAP.hudsizey);
	test += y2 * MAP.hudsize;
	return (MAP.huddata[(int)test]);
}

void	basehud(t_file *file)
{
	int x;
	int y;

	y = file->height - file->height / 8;
	while (y < file->height)
	{
		x = 0;
		while (x < file->width)
		{
			file->imgdata[x + y * file->width] = get_text_colorhud(file, x,
				y - (file->height - file->height / 8), file->height / 8);
			x++;
		}
		y++;
	}
}

void	inithud(t_file *file)
{
	int		bits;
	int		sl;
	int		endian;

	MAP.hudimg = mlx_xpm_file_to_image(MLX, "./textures/hud/hud.xpm",
		&MAP.hudsize, &MAP.hudsizey);
	MAP.huddata = (int *)mlx_get_data_addr(MAP.hudimg, &bits, &sl, &endian);
}

void	hud(t_file *file)
{
	inithud(file);
	initgun(file);
	basehud(file);
	updatehud(file, 0);
}
