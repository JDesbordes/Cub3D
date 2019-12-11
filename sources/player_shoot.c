/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player_shoot.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 03:09:06 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/08 07:23:01 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void	killenemy(t_file *file, t_enemy *enemy)
{
	t_enemy *temp;

	temp = MAP.enemies;
	Mix_PlayChannel(4, file->audio.death, 0);
	if (temp == enemy)
	{
		free(enemy);
		MAP.enemies = enemy->next;
	}
	while (temp)
	{
		if (temp->next == enemy)
		{
			free(enemy);
			temp->next = enemy->next;
			break ;
		}
		temp = temp->next;
	}
}

void	playershot(t_file *file, t_enemy *enemy)
{
	float x;
	float y;
	float angle;

	angle = PLAYER.rotation;
	angle *= M_PI / 180;
	x = sin(angle + M_PI);
	y = cos(angle);
	angle = atan2((enemy->y - PLAYER.y), (enemy->x - PLAYER.x)) - atan2(y, x);
	file->hit = 0;
	if (fabs(angle / M_PI * 180) < 6.5f)
	{
		x = enemy->x - PLAYER.x;
		y = enemy->y - PLAYER.y;
		if (enraycast(file, x, y, enemy))
		{
			enemy->hp -= 10;
			if (enemy->hp <= 0)
				killenemy(file, enemy);
		}
	}
}

void	setaudio(t_file *file)
{
	file->audio.death = Mix_LoadWAV("./audio/yoshi-ow.mp3");
	file->audio.shot = Mix_LoadWAV("./audio/try1.mp3");
	file->audio.damaged = Mix_LoadWAV("./audio/damaged.mp3");
	file->audio.coins = Mix_LoadWAV("./audio/COIN.mp3");
	file->audio.newlevel = Mix_LoadWAV("./audio/rupee-collect.mp3");
	file->audio.gameover = Mix_LoadWAV("./audio/gameover.mp3");
	file->audio.music = Mix_LoadMUS("./audio/music.mp3");
	Mix_PlayMusic(file->audio.music, -1);
	Mix_VolumeMusic(10);
}
