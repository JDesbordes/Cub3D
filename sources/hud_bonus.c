/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hud_bonus.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/24 21:06:38 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 13:04:47 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void	addscore(t_file *file)
{
	int i;

	i = 0;
	while (MAP.layout[i])
	{
		if (MAP.layout[i] == '2')
			MAP.score += 10;
		i++;
	}
}

void	checkscore(t_file *file)
{
	char *temp;

	if (PLAYER.score == MAP.score && MAP.nextlevel)
	{
		temp = MAP.nextlevel;
		freefile(file);
		readmap(file, MAP.nextlevel);
		mapcheck(file);
		free(temp);
		updatehud(file, 0);
		Mix_PlayChannel(4, file->audio.newlevel, 0);
	}
}

void	updatehud2(t_file *file, int option)
{
	int x;
	int y;

	y = file->height - file->height / 10;
	if (option == 0 || option == 2)
		while (y < file->height - file->height / 40)
		{
			x = file->width - file->width * 0.25;
			while (x < file->width - file->width * 0.05)
			{
				if (x < file->width - file->width *
					(0.25 - 0.20 * ((float)PLAYER.score / (float)MAP.score)))
					file->imgdata[x + y * file->width] = 0xffff00;
				else
					file->imgdata[x + y * file->width] = 0x393939;
				x++;
			}
			y++;
		}
	checkscore(file);
}

void	updatehud(t_file *file, int option)
{
	int x;
	int y;

	y = file->height - file->height / 10;
	if (option == 0 || option == 1)
	{
		while (y < file->height - file->height / 40)
		{
			x = file->width - file->width * 0.75;
			while (x < file->width - file->width * 0.55)
			{
				if (x < file->width - file->width *
					(0.75 - 0.20 * ((float)PLAYER.hp / 100.0)))
					file->imgdata[x + y * file->width] = 0xff0000;
				else
					file->imgdata[x + y * file->width] = 0x393939;
				x++;
			}
			y++;
		}
		if (PLAYER.hp <= 0)
			try(file, 2);
	}
	updatehud2(file, option);
}
