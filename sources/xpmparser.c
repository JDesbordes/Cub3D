/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   xpmparser.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 17:59:23 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/08 07:39:14 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

int		colorsp(t_file *file, float x, float current, int last)
{
	float	test;
	int		y;

	test = (x - (int)x) / MAP.swidth + 0.5;
	if (test > 1)
		test--;
	test = (int)(test * MAP.ssizex);
	y = (int)((current / last) * MAP.ssizex);
	test += y * MAP.ssizex;
	return (MAP.sptext[(int)test]);
}

void	printsprite(t_file *file, float inter[2], int x)
{
	int		lheight;
	int		ds;
	int		de;
	int		j;
	float	i;

	lheight = (int)(MAP.sheight * (file->height / file->dist));
	ds = -lheight / 1 + file->height / 2 + MAP.sheight * lheight * 2;
	de = lheight / 1 + file->height / 2 + MAP.sheight * lheight * 2;
	j = -1;
	if ((i = distance(inter[0], inter[1], MAP.nextsprite[x] % MAP.size,
		MAP.nextsprite[x] / MAP.size)) < MAP.swidth / 2)
	{
		if (inter[0] < MAP.nextsprite[x] % MAP.size)
			i *= -1;
		else if (inter[0] == MAP.nextsprite[x] % MAP.size &&
			inter[1] < MAP.nextsprite[x] / MAP.size)
			i *= -1;
		if (PLAYER.y < MAP.nextsprite[x] / MAP.size)
			i *= -1;
		while (++j < file->height - file->height / 8)
			if (j > ds && j < de && colorsp(file, i, j - ds, de - ds) != 0)
				file->imgdata[file->ray + (j * file->width)] =
					colorsp(file, i, j - ds, de - ds);
	}
}

void	calculateintersect(t_file *file, int i, float x, float y)
{
	float perpendicular;
	float startx;
	float starty;
	float intersect[2];
	float t;

	perpendicular = (PLAYER.rotation + 90) * M_PI / 180;
	intersect[0] = sin(perpendicular + M_PI);
	intersect[1] = cos(perpendicular);
	startx = MAP.nextsprite[i] % MAP.size;
	starty = MAP.nextsprite[i] / MAP.size;
	startx = startx - PLAYER.x;
	starty = starty - PLAYER.y;
	t = ((-startx) * intersect[1] + starty * intersect[0]) /
		((-x) * intersect[1] + y * intersect[0]);
	startx = x * t;
	starty = y * t;
	intersect[0] = PLAYER.x + startx;
	intersect[1] = PLAYER.y + starty;
	printsprite(file, intersect, i);
}

int		*otherreadxpm(t_file *file, char *str, char c)
{
	int		*data;
	int		y;
	int		bits;
	int		sl;
	int		endian;

	if (!checkdouble(file, c))
		return (NULL);
	if (c == 'N')
		if ((MAP.nimg = mlx_xpm_file_to_image(MLX, str, &MAP.nsize, &y)))
			data = (int *)mlx_get_data_addr(MAP.nimg, &bits, &sl, &endian);
	if (c == 'S')
		if ((MAP.simg = mlx_xpm_file_to_image(MLX, str, &MAP.ssize, &y)))
			data = (int *)mlx_get_data_addr(MAP.simg, &bits, &sl, &endian);
	if (c == 'E')
		if ((MAP.eimg = mlx_xpm_file_to_image(MLX, str, &MAP.esize, &y)))
			data = (int *)mlx_get_data_addr(MAP.eimg, &bits, &sl, &endian);
	if (c == 'W')
		if ((MAP.wimg = mlx_xpm_file_to_image(MLX, str, &MAP.wsize, &y)))
			data = (int *)mlx_get_data_addr(MAP.wimg, &bits, &sl, &endian);
	return (data);
}

int		*readxpm(t_file *file, char *str, char c)
{
	int		*data;
	int		bits;
	int		sl;
	int		endian;

	if (!checkdouble(file, c))
		return (NULL);
	if (c == 'A')
		if ((MAP.aimg =
			mlx_xpm_file_to_image(MLX, str, &MAP.asizex, &MAP.asizey)))
			data = (int *)mlx_get_data_addr(MAP.aimg, &bits, &sl, &endian);
	if (c == 'B')
		if ((MAP.a2img =
			mlx_xpm_file_to_image(MLX, str, &MAP.a2sizex, &MAP.a2sizey)))
			data = (int *)mlx_get_data_addr(MAP.a2img, &bits, &sl, &endian);
	if (c == 'C')
		if ((MAP.a3img =
			mlx_xpm_file_to_image(MLX, str, &MAP.a3sizex, &MAP.a3sizey)))
			data = (int *)mlx_get_data_addr(MAP.a3img, &bits, &sl, &endian);
	if (c == 'P')
		if ((MAP.pimg =
			mlx_xpm_file_to_image(MLX, str, &MAP.ssizex, &MAP.ssizey)))
			data = (int *)mlx_get_data_addr(MAP.pimg, &bits, &sl, &endian);
	return (data);
}
