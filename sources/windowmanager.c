/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   windowmanager.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 14:31:45 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 17:38:11 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void	windowmanager(t_file *file)
{
	int		bits;
	int		sizeline;
	int		end;

	file->win = mlx_new_window(MLX, file->width, file->height, "Cube4D");
	file->img = mlx_new_image(MLX, file->width, file->height);
	file->imgdata = (int *)mlx_get_data_addr(file->img, &bits, &sizeline, &end);
	hud(file);
	mlx_loop_hook(MLX, raycastgen, (void *)file);
	mlx_hook(file->win, 2, 0, holdinput, (void *)file);
	mlx_hook(file->win, 3, 0, releaseinput, (void *)file);
	mlx_hook(file->win, 17, 0, try, (void *)file);
	mlx_loop(MLX);
}

int		get_text_colorn(t_file *file, float x, float current, int last)
{
	float		test;
	int			y;

	test = x - (int)x + 0.5;
	if (test > 1)
		test--;
	test = (int)(test * MAP.nsize);
	y = (int)((current / last) * MAP.nsize);
	test += y * MAP.nsize;
	return (MAP.ntext[(long int)test]);
}

int		get_text_colors(t_file *file, float x, float current, int last)
{
	float	test;
	int		y;

	test = 1 - (x - (int)x + 0.5);
	if (test < 1)
		test++;
	test = (int)(test * MAP.ssize);
	y = (int)((current / last) * MAP.ssize);
	test += y * MAP.ssize;
	return (MAP.stext[(int)test]);
}

int		get_text_colore(t_file *file, float x, float current, int last)
{
	float	test;
	int		y;

	test = x - (int)x + 0.5;
	if (test > 1)
		test--;
	test = (int)(test * MAP.esize);
	y = (int)((current / last) * MAP.esize);
	test += y * MAP.esize;
	return (MAP.etext[(int)test]);
}

int		get_text_colorw(t_file *file, float x, float current, int last)
{
	float	test;
	int		y;

	test = 1 - (x - (int)x + 0.5);
	if (test < 0)
		test++;
	test = (int)(test * MAP.wsize);
	y = (int)((current / last) * MAP.wsize);
	test += y * MAP.wsize;
	return (MAP.wtext[(int)test]);
}
