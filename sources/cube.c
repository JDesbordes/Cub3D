/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 16:42:43 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 20:11:53 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"
#include <time.h>

int		try(t_file *file, int option)
{
	if (option != 0)
		mlx_destroy_image(MLX, file->img);
	if (option != 3 && option != 0)
		mlx_destroy_window(MLX, file->win);
	freeallfiles(file);
	if (option == 2)
		Mix_PlayChannel(2, Mix_LoadWAV("./audio/gameover.mp3"), 0);
	Mix_HaltMusic();
	while (Mix_Playing(2) != 0)
		SDL_Delay(200);
	Mix_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
	return (1);
}

int		holdinput(int i, t_file *file)
{
	if (i == 123)
		PLAYER.inputleftar = 1;
	else if (i == 124)
		PLAYER.inputrightar = 1;
	if (i == 13)
		PLAYER.inputw = 1;
	if (i == 0)
		PLAYER.inputa = 1;
	if (i == 1)
		PLAYER.inputs = 1;
	if (i == 2)
		PLAYER.inputd = 1;
	if (i == 53)
		try(file, 1);
	if (i == 49 && PLAYER.inputshot == 0)
	{
		Mix_PlayChannel(3, file->audio.shot, 0);
		PLAYER.inputshot = 1;
	}
	return (0);
}

int		releaseinput(int i, t_file *file)
{
	if (i == 123)
		PLAYER.inputleftar = 0;
	else if (i == 124)
		PLAYER.inputrightar = 0;
	if (i == 13)
		PLAYER.inputw = 0;
	if (i == 0)
		PLAYER.inputa = 0;
	if (i == 1)
		PLAYER.inputs = 0;
	if (i == 2)
		PLAYER.inputd = 0;
	if (i == 49)
		PLAYER.inputshot = 0;
	return (0);
}

int		cube3d(char *map, char *option)
{
	t_file	*file;

	if (!(file = malloc(sizeof(t_file))))
		return (1);
	file->oldwidth = 0;
	file->oldheight = 0;
	MAP.huddata = NULL;
	MAP.gundata = NULL;
	MLX = mlx_init();
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	setaudio(file);
	readmap(file, map);
	mapcheck(file);
	if (option)
	{
		smile(file);
		try(file, 3);
	}
	windowmanager(file);
	return (1);
}

int		main(int ac, char **argv)
{
	if (ac > 3 || ac < 2)
		ft_printf("%sNeed two arguments\n", "Error\n");
	if (ac >= 2 && checkcub(argv[1], argv[2], ac))
		return (0);
	else if (ac == 2)
		cube3d(argv[1], NULL);
	else if (ac == 3)
		cube3d(argv[1], argv[2]);
	return (0);
}
