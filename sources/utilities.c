/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utilities.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/23 14:46:50 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 13:33:46 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

float	distance(float x1, float y1, float x2, float y2)
{
	float i;
	float j;
	float sum;

	i = (x2 - x1) * (x2 - x1);
	j = (y2 - y1) * (y2 - y1);
	sum = sqrt(i + j);
	return (sum);
}

void	setxiyi(t_file *file, float *xi, float *yi)
{
	*xi = -(PLAYER.x - (int)PLAYER.x);
	if ((PLAYER.x - (int)PLAYER.x) > 0.5)
	{
		*xi *= -1;
		*xi = 1 - *xi;
	}
	*yi = -(PLAYER.y - (int)PLAYER.y);
	if ((PLAYER.y - (int)PLAYER.y) > 0.5)
	{
		*yi *= -1;
		*yi = 1 - *yi;
	}
}

int		checkd(t_file *file, float interx[2], float intery[2])
{
	return (distance(PLAYER.x, PLAYER.y, interx[0], interx[1]) <
	distance(PLAYER.x, PLAYER.y, intery[0], intery[1]));
}

int		checkplayer(t_file *file, int i)
{
	if (PLAYER.x != -1 || PLAYER.y != -1)
		return (0);
	PLAYER.x = i % MAP.size;
	PLAYER.y = i / MAP.size;
	if (MAP.layout[i] == 'N' || MAP.layout[i] == 'S')
		PLAYER.rotation = MAP.layout[i] == 'N' ? 180 : 0;
	if (MAP.layout[i] == 'E' || MAP.layout[i] == 'W')
		PLAYER.rotation = MAP.layout[i] == 'E' ? 270 : 90;
	MAP.layout[i] = '0';
	return (1);
}
