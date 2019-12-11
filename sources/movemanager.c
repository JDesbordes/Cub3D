/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   movemanager.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 14:23:14 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/05 04:08:17 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void	movew(t_file *file)
{
	float angle;
	float newx;
	float newy;

	angle = PLAYER.rotation;
	angle < 0 ? angle += 360 : angle;
	angle *= M_PI / 180;
	newx = PLAYER.x + sin(angle + M_PI) / 15;
	if (!collision(file, newx, PLAYER.y))
		PLAYER.x += sin(angle + M_PI) / 15;
	newy = PLAYER.y + cos(angle) / 15;
	if (!collision(file, PLAYER.x, newy))
		PLAYER.y += cos(angle) / 15;
}

void	moves(t_file *file)
{
	float angle;
	float newx;
	float newy;

	angle = PLAYER.rotation - 180;
	angle < 0 ? angle += 360 : angle;
	angle *= M_PI / 180;
	newx = PLAYER.x + sin(angle + M_PI) / 15;
	if (!collision(file, newx, PLAYER.y))
		PLAYER.x += sin(angle + M_PI) / 15;
	newy = PLAYER.y + cos(angle) / 15;
	if (!collision(file, PLAYER.x, newy))
		PLAYER.y += cos(angle) / 15;
}

void	movea(t_file *file)
{
	float angle;
	float newx;
	float newy;

	angle = PLAYER.rotation - 90;
	angle < 0 ? angle += 360 : angle;
	angle *= M_PI / 180;
	newx = PLAYER.x + sin(angle + M_PI) / 15;
	if (!collision(file, newx, PLAYER.y))
		PLAYER.x += sin(angle + M_PI) / 15;
	newy = PLAYER.y + cos(angle) / 15;
	if (!collision(file, PLAYER.x, newy))
		PLAYER.y += cos(angle) / 15;
}

void	moved(t_file *file)
{
	float angle;
	float newx;
	float newy;

	angle = PLAYER.rotation + 90;
	angle < 0 ? angle += 360 : angle;
	angle *= M_PI / 180;
	newx = PLAYER.x + sin(angle + M_PI) / 15;
	if (!collision(file, newx, PLAYER.y))
		PLAYER.x += sin(angle + M_PI) / 15;
	newy = PLAYER.y + cos(angle) / 15;
	if (!collision(file, PLAYER.x, newy))
		PLAYER.y += cos(angle) / 15;
}

int		move(t_file *file)
{
	if (PLAYER.inputleftar)
		PLAYER.rotation -= 2;
	if (PLAYER.inputrightar)
		PLAYER.rotation += 2;
	if (PLAYER.inputw)
		movew(file);
	if (PLAYER.inputa)
		movea(file);
	if (PLAYER.inputs)
		moves(file);
	if (PLAYER.inputd)
		moved(file);
	return (0);
}
