/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   enemy_renderer.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/25 16:25:58 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 20:21:42 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

int		checkshot(t_file *file, t_enemy *temp)
{
	float x;
	float y;

	x = temp->x - PLAYER.x;
	y = temp->y - PLAYER.y;
	file->hit = 0;
	if (enraycast(file, x, y, temp))
		return (1);
	return (0);
}

void	shootmanager(t_file *file)
{
	t_enemy *temp;

	temp = MAP.enemies;
	while (temp)
	{
		if (PLAYER.inputshot == 1)
			playershot(file, temp);
		if (!(file->now % 10))
		{
			if (temp->shot == 0 && checkshot(file, temp))
			{
				temp->shot = 1;
				PLAYER.hp -= 15;
				Mix_PlayChannel(2, file->audio.damaged, 0);
				updatehud(file, 1);
			}
			else
				temp->shot = 2;
		}
		else if (temp->shot != 0 && file->now % 10)
			temp->shot = 0;
		temp = temp->next;
	}
	if (PLAYER.inputshot == 1)
		PLAYER.inputshot = 2;
}

int		colorenemy(t_file *file, float x, float current, int last)
{
	float	test;
	int		y;

	test = (x - (int)x) / 0.5 + 0.5;
	if (test > 1)
		test--;
	test = (int)(test * MAP.asizex);
	y = (int)((current / last) * MAP.asizey);
	test += y * MAP.asizex;
	if (!(file->now % 10))
		return (MAP.a3text[(int)test]);
	if (file->now % 2)
		return (MAP.a2text[(int)test]);
	else
		return (MAP.atext[(int)test]);
}

void	printenemy(t_file *file, float inter[2], t_enemy *x)
{
	int		lheight;
	int		ds;
	int		de;
	int		j;
	float	i;

	file->dist = distance(PLAYER.x, PLAYER.y, x->x, x->y);
	lheight = (int)(1 * (file->height / file->dist));
	ds = -lheight / 1 + file->height / 2 + 0.25 * lheight * 2;
	de = lheight / 1 + file->height / 2;
	j = -1;
	if ((i = distance(inter[0], inter[1], x->x,
		x->y)) < MAP.swidth / 2)
	{
		if (inter[0] < x->x || (inter[0] == x->x && inter[1] < x->y))
			i *= -1;
		if (PLAYER.y < x->y)
			i *= -1;
		while (++j < file->height - file->height / 8)
			if (j > ds && j < de && colorenemy(file, i, j - ds, de - ds) != 0)
				file->imgdata[file->ray + (j * file->width)] =
					colorenemy(file, i, j - ds, de - ds);
	}
}

int		calcenemy(t_file *file, t_enemy *i, float x, float y)
{
	float perpendicular;
	float startx;
	float starty;
	float e[2];
	float t;

	perpendicular = (PLAYER.rotation + 90) * M_PI / 180;
	e[0] = sin(perpendicular + M_PI);
	e[1] = cos(perpendicular);
	startx = i->x;
	starty = i->y;
	startx = startx - PLAYER.x;
	starty = starty - PLAYER.y;
	t = ((-startx) * e[1] + starty * e[0]) / ((-x) * e[1] + y * e[0]);
	startx = x * t;
	starty = y * t;
	e[0] = PLAYER.x + startx;
	e[1] = PLAYER.y + starty;
	if (distance(i->x, i->y, e[0], e[1]) < 0.5f && distance(PLAYER.x, PLAYER.y,
	i->x, i->y) < file->dist && ((x >= 0 && e[0] - PLAYER.x >= 0) || (x <= 0 &&
	e[0] - PLAYER.x <= 0)) && ((y >= 0 && e[1] - PLAYER.y >= 0) || (y <= 0 &&
	e[1] - PLAYER.y <= 0)))
		printenemy(file, e, i);
	file->dist2 = distance(PLAYER.x, PLAYER.y, i->x, i->y);
	return (1);
}
