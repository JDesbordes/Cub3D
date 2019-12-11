/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   enemy_shoot.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 01:19:25 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 03:02:00 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void			encheckwall(t_file *file, float x, float y, char inter)
{
	int i;

	if (x > 0.0 && x < MAP.size - 1 && y > 0.0 && y < MAP.maplines - 1)
	{
		if (inter == 'x')
		{
			i = (y - (int)y < 0.5 ? (int)y : (int)y + 1);
			i = i * MAP.size + (PLAYER.x > x ? (int)x : (int)x + 1);
			if (MAP.layout[i] == '1')
				file->hit = 1;
		}
		else if (inter == 'y')
		{
			i = (PLAYER.y > y ? (int)y : (int)y + 1);
			i = i * MAP.size + (x - (int)x < 0.5 ? (int)x : (int)x + 1);
			if (MAP.layout[i] == '1')
				file->hit = 1;
		}
	}
}

static int		test(t_file *file, t_enemy *enemy, float intx[2], float inty[2])
{
	if ((distance(PLAYER.x, PLAYER.y, enemy->x, enemy->y)
		< distance(intx[0], intx[1], PLAYER.x, PLAYER.y))
		&& (distance(PLAYER.x, PLAYER.y, enemy->x, enemy->y)
		< distance(inty[0], inty[1], PLAYER.x, PLAYER.y)))
		return (1);
	return (0);
}

int				enraycast(t_file *file, float x, float y, t_enemy *enemy)
{
	float	xyi[2];
	float	intx[2];
	float	inty[2];

	setxiyi(file, &xyi[0], &xyi[1]);
	xyi[1] += (y > 0 ? 0.5 : -0.5);
	xyi[0] += (x > 0 ? 0.5 : -0.5);
	while (!file->hit && fabs(xyi[0]) < MAP.size && fabs(xyi[1]) < MAP.maplines)
	{
		intx[0] = PLAYER.x + xyi[0];
		intx[1] = PLAYER.y + fabs(xyi[0]) * (y / fabs(x));
		inty[0] = PLAYER.x + fabs(xyi[1]) * (x / fabs(y));
		inty[1] = PLAYER.y + xyi[1];
		if (fabs(y) < 0.001 || (fabs(x) > 0.001 && checkd(file, intx, inty)))
		{
			encheckwall(file, intx[0], intx[1], 'x');
			x < 0 ? xyi[0]-- : xyi[0]++;
		}
		else
		{
			encheckwall(file, inty[0], inty[1], 'y');
			y < 0 ? xyi[1]-- : xyi[1]++;
		}
	}
	return (test(file, enemy, intx, inty));
}
