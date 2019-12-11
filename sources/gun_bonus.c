/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gun_bonus.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/24 22:37:34 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 18:54:20 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void	initgun(t_file *file)
{
	int		bits;
	int		sl;
	int		endian;

	MAP.gunimg = mlx_xpm_file_to_image(MLX, "./textures/hud/gun.xpm",
	&MAP.gunsize, &MAP.gunsizey);
	MAP.gundata = (int *)mlx_get_data_addr(MAP.gunimg, &bits, &sl, &endian);
}

int		get_text_colorgun(t_file *file, float x, float y, int last)
{
	float	test;
	int		y2;

	if (file->width < 2 || file->height < 2)
		return (0);
	test = (int)((x / (file->width / 2)) * MAP.gunsize);
	y2 = (int)((y / last) * MAP.gunsizey);
	test += y2 * MAP.gunsize;
	return (MAP.gundata[(int)test]);
}

void	rendergun(t_file *file)
{
	int x;
	int y;
	int result;

	x = file->width / 2;
	y = file->height / 2;
	while (y < file->height - file->height / 8)
	{
		x = file->width / 2;
		while (x < file->width)
		{
			if ((result = get_text_colorgun(file, x - file->width / 2,
				y - file->height / 2, file->height / 2)) != 0)
				file->imgdata[x + y * file->width] = result;
			x++;
		}
		y++;
	}
}
