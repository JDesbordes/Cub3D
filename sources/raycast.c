/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycast.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/16 12:41:27 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 15:33:34 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cube.h"

void	checkwally(t_file *file, float x, float y)
{
	int i;

	i = (PLAYER.y > y ? (int)y : (int)y + 1);
	i = i * MAP.size + (x - (int)x < 0.5 ? (int)x : (int)x + 1);
	file->side = 1;
	if (MAP.layout[i] == '1')
		printfwall(file, x, y);
	else if (MAP.layout[i] == '2')
	{
		MAP.nextsprite[MAP.currentsp] = i;
		MAP.currentsp++;
	}
}

void	checkwall(t_file *file, float x, float y, char inter)
{
	int i;

	if (x > 0.0 && x < MAP.size - 1 && y > 0.0 && y < MAP.maplines - 1)
	{
		if (inter == 'x')
		{
			i = (y - (int)y < 0.5 ? (int)y : (int)y + 1);
			i = i * MAP.size + (PLAYER.x > x ? (int)x : (int)x + 1);
			file->side = 0;
			if (MAP.layout[i] == '1')
				printfwall(file, x, y);
			else if (MAP.layout[i] == '2')
			{
				MAP.nextsprite[MAP.currentsp] = i;
				MAP.currentsp++;
			}
		}
		else if (inter == 'y')
			checkwally(file, x, y);
	}
}

void	raycast(t_file *file, float x, float y)
{
	float	xi;
	float	yi;
	float	intx[2];
	float	inty[2];

	setxiyi(file, &xi, &yi);
	yi += (y > 0 ? 0.5 : -0.5);
	xi += (x > 0 ? 0.5 : -0.5);
	while (!file->hit && fabs(xi) < MAP.size && fabs(yi) < MAP.maplines)
	{
		intx[0] = PLAYER.x + xi;
		intx[1] = PLAYER.y + fabs(xi) * (y / fabs(x));
		inty[0] = PLAYER.x + fabs(yi) * (x / fabs(y));
		inty[1] = PLAYER.y + yi;
		if (fabs(y) < 0.001 || (fabs(x) > 0.001 && checkd(file, intx, inty)))
		{
			checkwall(file, intx[0], intx[1], 'x');
			x < 0 ? xi-- : xi++;
		}
		else
		{
			checkwall(file, inty[0], inty[1], 'y');
			y < 0 ? yi-- : yi++;
		}
	}
}

void	resetsp(t_file *file)
{
	int i;

	i = 0;
	while (MAP.nextsprite[i] != 0)
	{
		MAP.nextsprite[i] = 0;
		i++;
	}
	file->dist2 = MAP.size;
}

int		raycastgen(t_file *file)
{
	float	i;
	float	angle;

	move(file);
	file->now = time(NULL);
	shootmanager(file);
	i = 0;
	while (i < file->width)
	{
		resetsp(file);
		file->hit = 0;
		file->ray = i;
		angle = PLAYER.rotation - (60 / 2) + (i * (60.0 / (float)file->width));
		file->rayangle = angle;
		angle *= M_PI / 180;
		raycast(file, sin(angle + M_PI), cos(angle));
		i += 1;
	}
	rendergun(file);
	moveall(file);
	if (!file->setup)
		mlx_put_image_to_window(MLX, file->win, file->img, 0, 0);
	return (1);
}
