/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   freefile.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/23 17:17:04 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 15:21:58 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void	enemyfree(t_file *file)
{
	t_enemy *temp;

	while (MAP.enemies)
	{
		temp = MAP.enemies->next;
		free(MAP.enemies);
		MAP.enemies = temp;
	}
}

void	freefile2(t_file *file)
{
	if (MAP.ssize)
		mlx_destroy_image(MLX, MAP.simg);
	if (MAP.wsize)
		mlx_destroy_image(MLX, MAP.wimg);
	if (MAP.esize)
		mlx_destroy_image(MLX, MAP.eimg);
	if (MAP.ssizex)
		mlx_destroy_image(MLX, MAP.pimg);
	if (MAP.asizex)
		mlx_destroy_image(MLX, MAP.aimg);
	if (MAP.a2sizex)
		mlx_destroy_image(MLX, MAP.a2img);
	if (MAP.a3sizex)
		mlx_destroy_image(MLX, MAP.a3img);
	free(MAP.nextsprite);
	enemyfree(file);
}

void	freefile(t_file *file)
{
	if (MAP.layout)
		free(MAP.layout);
	if (MAP.nsize)
		mlx_destroy_image(MLX, MAP.nimg);
	freefile2(file);
}

void	freeallfiles(t_file *file)
{
	if (MAP.huddata)
		mlx_destroy_image(MLX, MAP.hudimg);
	if (MAP.gundata)
		mlx_destroy_image(MLX, MAP.gunimg);
	if (MAP.nextlevel)
		free(MAP.nextlevel);
	Mix_FreeChunk(file->audio.death);
	Mix_FreeChunk(file->audio.shot);
	Mix_FreeChunk(file->audio.damaged);
	Mix_FreeChunk(file->audio.coins);
	Mix_FreeChunk(file->audio.newlevel);
	Mix_FreeChunk(file->audio.gameover);
	Mix_FreeMusic(file->audio.music);
	freefile(file);
	free(file);
}

void	freeandout(t_file *file, char *str, char *print)
{
	if (str)
		free(str);
	ft_printf("%s%s\n", "Error\n", print);
	try(file, 0);
}
