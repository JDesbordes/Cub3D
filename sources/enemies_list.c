/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   enemies_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/25 14:01:07 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 11:38:15 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void		enemy_add_front(t_enemy **alst, t_enemy *new)
{
	new->next = *alst;
	*alst = new;
}

t_enemy		*newenemy(t_file *file, int i, int id)
{
	t_enemy *new;

	if (!(new = malloc(sizeof(t_enemy) * 1)))
		return (NULL);
	new->x = i % MAP.size;
	new->y = (int)(i / MAP.size);
	new->id = id;
	if (id % 2)
	{
		new->destination = i;
		new->destination2 = -1;
	}
	else
	{
		new->destination2 = i;
		new->destination = -1;
	}
	new->shot = 0;
	new->hp = 20;
	enemy_add_front(&MAP.enemies, new);
	return (new);
}

t_enemy		*findbyid(t_file *file, int id)
{
	t_enemy *temp;

	temp = MAP.enemies;
	while (temp && temp->next && temp->id != id)
		temp = temp->next;
	if (temp && temp->id == id)
		return (temp);
	return (NULL);
}

void		enemygen(t_file *file, int i)
{
	t_enemy *temp;

	if (MAP.layout[i] >= '3' && MAP.layout[i] <= '9')
	{
		if ((temp = findbyid(file, MAP.layout[i] - 48)) != NULL)
		{
			if (temp->id % 2)
				temp->destination2 = i;
			else
				temp->destination = i;
		}
		else
			newenemy(file, i, MAP.layout[i] - 48);
		MAP.layout[i] = '0';
	}
}
