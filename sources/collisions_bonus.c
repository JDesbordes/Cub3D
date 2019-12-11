/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   collisions_bonus.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/23 17:53:04 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 13:38:24 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

int		collision(t_file *file, float x, float y)
{
	int i;

	y += 0.5;
	x += 0.5;
	i = (int)x + (int)y * MAP.size;
	if (MAP.layout[i] == '1')
		return (1);
	if (MAP.layout[i] == '2')
	{
		Mix_PlayChannel(4, file->audio.coins, 0);
		MAP.layout[i] = '0';
		PLAYER.score += 10;
		updatehud(file, 0);
	}
	return (0);
}

t_enemy	*farthest(t_file *file)
{
	t_enemy	*temp;
	t_enemy	*far;

	temp = MAP.enemies;
	far = NULL;
	while (temp)
	{
		if (file->dist > distance(PLAYER.x, PLAYER.y, temp->x, temp->y) &&
		file->dist2 > distance(PLAYER.x, PLAYER.y, temp->x, temp->y))
			if (!far || distance(PLAYER.x, PLAYER.y, temp->x, temp->y) >
			distance(PLAYER.x, PLAYER.y, far->x, far->y))
			{
				far = temp;
			}
		temp = temp->next;
	}
	return (far);
}

void	calcorder(t_file *file, float angle)
{
	float	angles[2];
	t_enemy	*temp;

	angle *= M_PI / 180;
	angles[0] = sin(angle + M_PI);
	angles[1] = cos(angle);
	temp = farthest(file);
	while (MAP.currentsp > 0 || temp)
	{
		if (MAP.currentsp > 0 && (!temp ||
		distance(PLAYER.x, PLAYER.y, MAP.nextsprite[MAP.currentsp - 1] %
			MAP.size, MAP.nextsprite[MAP.currentsp - 1] / MAP.size) >
			distance(PLAYER.x, PLAYER.y, temp->x, temp->y)))
		{
			file->dist = distance(PLAYER.x, PLAYER.y,
			MAP.nextsprite[MAP.currentsp - 1] % MAP.size,
			MAP.nextsprite[MAP.currentsp - 1] / MAP.size);
			calculateintersect(file, MAP.currentsp - 1, angles[0], angles[1]);
			MAP.currentsp--;
		}
		else if (temp && calcenemy(file, temp, angles[0], angles[1]))
			temp = farthest(file);
	}
}

int		checkdouble(t_file *file, char c)
{
	if (c == 'N' && MAP.nsize != 0)
		return ((int)(MAP.nimg = NULL));
	else if (c == 'E' && MAP.esize != 0)
		return ((int)(MAP.eimg = NULL));
	else if (c == 'S' && MAP.ssize != 0)
		return ((int)(MAP.simg = NULL));
	else if (c == 'W' && MAP.wsize != 0)
		return ((int)(MAP.wimg = NULL));
	else if (c == 'P' && MAP.ssizex != 0)
		return ((int)(MAP.pimg = NULL));
	else if (c == 'A' && MAP.asizex != 0)
		return ((int)(MAP.aimg = NULL));
	else if (c == 'B' && MAP.a2sizex != 0)
		return ((int)(MAP.a2img = NULL));
	else if (c == 'C' && MAP.a3sizex != 0)
		return ((int)(MAP.a3img = NULL));
	return (1);
}

int		checkcub(char *map, char *option, int ac)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_split(map, '.');
	while (temp[i])
	{
		i++;
		if (temp[i])
			free(temp[i - 1]);
	}
	if (ft_strncmp(temp[i - 1], "cub", 4))
	{
		ft_printf("%sMAP NOT IN .cub\n", "Error\n");
		free(temp[i - 1]);
		free(temp);
		return (1);
	}
	free(temp[i - 1]);
	free(temp);
	if (ac == 3)
		if (ft_strncmp(option, "--save", 7))
			return (ft_printf("%sIncorrect flag try --save\n", "Error\n"));
	return (0);
}
