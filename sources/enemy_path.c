/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   enemy_path.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/28 15:58:37 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/04 21:25:51 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void	moveenemy(t_file *file, t_enemy *target)
{
	float	x;
	float	y;
	int		temp;

	x = (target->destination2 % MAP.size) - (target->destination % MAP.size);
	x /= distance(target->destination % MAP.size,
		target->destination / MAP.size, target->destination2 % MAP.size,
		target->destination2 / MAP.size);
	y = (target->destination2 / MAP.size) - (target->destination / MAP.size);
	y /= distance(target->destination % MAP.size,
		target->destination / MAP.size, target->destination2 % MAP.size,
		target->destination2 / MAP.size);
	target->x += x / 50;
	target->y += y / 50;
	if (distance(target->destination % MAP.size,
		target->destination / MAP.size, target->destination2 % MAP.size,
		target->destination2 / MAP.size) <
		distance(target->destination % MAP.size,
		target->destination / MAP.size, target->x, target->y))
	{
		temp = target->destination;
		target->destination = target->destination2;
		target->destination2 = temp;
	}
}

void	moveall(t_file *file)
{
	t_enemy *temp;

	temp = MAP.enemies;
	while (temp)
	{
		if (temp->destination2 > 0 && temp->destination > 0)
			moveenemy(file, temp);
		temp = temp->next;
	}
}
