/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mapcheck.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/15 20:03:56 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 13:01:17 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cube.h"

void	mapinit2(t_file *file)
{
	PLAYER.rotation = -1;
	file->fov = 90;
	PLAYER.inputleftar = 0;
	PLAYER.inputrightar = 0;
	PLAYER.inputw = 0;
	PLAYER.inputa = 0;
	PLAYER.inputs = 0;
	PLAYER.inputd = 0;
	PLAYER.score = 0;
	PLAYER.hp = 100;
	PLAYER.inputshot = 0;
	MAP.currentsp = 0;
	MAP.nimg = NULL;
	MAP.simg = NULL;
	MAP.wimg = NULL;
	MAP.eimg = NULL;
	MAP.pimg = NULL;
	MAP.aimg = NULL;
	MAP.a2img = NULL;
	MAP.a3img = NULL;
	MAP.nextsprite = ft_calloc(sizeof(int), 50);
	file->setup = 0;
}

void	mapinit(t_file *file)
{
	MAP.nsize = 0;
	file->width = 0;
	file->height = 0;
	MAP.ssize = 0;
	MAP.wsize = 0;
	MAP.esize = 0;
	MAP.ssizex = 0;
	MAP.asizex = 0;
	MAP.a2sizex = 0;
	MAP.nextlevel = NULL;
	MAP.a3sizex = 0;
	MAP.ftext = -1;
	MAP.ctext = -1;
	MAP.layout = NULL;
	MAP.size = 0;
	MAP.maplines = 0;
	MAP.swidth = 0.5;
	MAP.sheight = 0.5;
	MAP.score = 0;
	MAP.enemies = NULL;
	PLAYER.x = -1;
	PLAYER.y = -1;
	mapinit2(file);
}

void	checktext(t_file *file)
{
	if (MAP.atext == NULL)
		freeandout(file, NULL, "enemies missing texture A");
	else if (MAP.a2text == NULL)
		freeandout(file, NULL, "enemies missing texture A2");
	else if (MAP.a3text == NULL)
		freeandout(file, NULL, "enemies missing texture A3(shot)");
}

void	checkwalls(t_file *file)
{
	int i;

	i = 0;
	while (MAP.layout[i])
	{
		if (MAP.layout[i] != '1' && (i < MAP.size || i % MAP.size == 0 || i %
			MAP.size == MAP.size - 1 || i > (MAP.maplines - 1) * MAP.size - 1))
			freeandout(file, NULL, "Gap in map walls");
		if (MAP.layout[i] == 'N' || MAP.layout[i] == 'S' ||
			MAP.layout[i] == 'E' || MAP.layout[i] == 'W')
		{
			if (!checkplayer(file, i))
				freeandout(file, NULL, "More than one player on the map");
		}
		else if (!(MAP.layout[i] >= '0' && MAP.layout[i] <= '9'))
			freeandout(file, NULL, "Unexpected character");
		enemygen(file, i);
		i++;
	}
	checktext(file);
}

void	mapcheck(t_file *file)
{
	if (MAP.nimg == NULL)
		freeandout(file, NULL, "No/Extra North texture");
	else if (MAP.eimg == NULL)
		freeandout(file, NULL, "No/Extra East texture");
	else if (MAP.wimg == NULL)
		freeandout(file, NULL, "No/Extra West texture");
	else if (MAP.simg == NULL)
		freeandout(file, NULL, "No/Extra South texture");
	else if (MAP.pimg == NULL)
		freeandout(file, NULL, "No/Extra Sprite texture");
	else if (MAP.ftext == -1)
		freeandout(file, NULL, "No/Extra Floor color");
	else if (MAP.ctext == -1)
		freeandout(file, NULL, "No/Extra Ceiling color");
	else if (MAP.layout == NULL)
		freeandout(file, NULL, "no/Extra layout");
	else if (MAP.size <= 0 || MAP.maplines <= 0)
		freeandout(file, NULL, "map of invalid size");
	else if (file->height <= 0 || file->width <= 0)
		freeandout(file, NULL, "bad screen dimensions");
	checkwalls(file);
}
