/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 16:47:59 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 14:45:40 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../Libftprintf/includes/ft_printf.h"
# include "../minilibx/mlx.h"
# include "SDL.h"
# include "SDL_mixer.h"
# include <math.h>
# include <time.h>

# define SCREENHEIGHT 2880
# define SCREENWIDTH 5120
# define MAP file->map
# define PLAYER file->player
# define MLX file->mlx

typedef struct		s_audio
{
	Mix_Music		*music;

	Mix_Chunk		*death;
	Mix_Chunk		*shot;
	Mix_Chunk		*damaged;
	Mix_Chunk		*coins;
	Mix_Chunk		*newlevel;
	Mix_Chunk		*gameover;
}					t_audio;

typedef	struct		s_enemy
{
	float			x;
	float			y;

	int				destination;
	int				destination2;
	int				shot;

	int				hp;

	int				id;
	void			*next;
}					t_enemy;

typedef	struct		s_map
{
	int				*ntext;
	int				*stext;
	int				*wtext;
	int				*etext;
	void			*nimg;
	void			*simg;
	void			*wimg;
	void			*eimg;
	int				nsize;
	int				ssize;
	int				wsize;
	int				esize;

	int				*sptext;
	void			*pimg;
	int				ssizex;
	int				ssizey;
	float			swidth;
	float			sheight;

	int				*atext;
	void			*aimg;
	int				asizex;
	int				asizey;

	int				*a3text;
	void			*a3img;
	int				a3sizex;
	int				a3sizey;

	int				*a2text;
	void			*a2img;
	int				a2sizex;
	int				a2sizey;

	int				*huddata;
	void			*hudimg;
	int				hudsize;
	int				hudsizey;

	int				*gundata;
	void			*gunimg;
	int				gunsize;
	int				gunsizey;

	int				score;

	char			*nextlevel;
	int				ftext;
	int				ctext;
	int				*nextsprite;
	int				currentsp;
	char			*layout;
	int				size;
	int				maplines;

	int				nbenemies;
	t_enemy			*enemies;
}					t_map;

typedef struct		s_player
{
	float			x;
	float			y;
	float			rotation;

	int				inputleftar;
	int				inputrightar;
	int				inputw;
	int				inputa;
	int				inputs;
	int				inputd;
	int				inputshot;

	int				score;
	int				hp;
}					t_player;

typedef struct		s_file
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*imgdata;
	int				direction;

	time_t			now;
	int				drawstart;
	int				drawend;
	int				hit;
	int				side;
	float			dist;
	float			dist2;
	int				ray;
	t_map			map;
	t_player		player;
	t_audio			audio;

	int				setup;
	int				raydirection;
	float			rayangle;
	int				fov;
	int				height;
	int				width;
	int				oldwidth;
	int				oldheight;
}					t_file;

typedef struct		s_header
{
	unsigned char	bitmap_type[2];
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
}					t_header;

typedef struct		s_header2
{
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}					t_header2;

void				mapinit(t_file	*file);
void				mapcheck(t_file	*file);
void				readmap(t_file *file, char *map);
int					raycastgen(t_file *file);
int					setimage(t_file	*file);
int					move(t_file *file);
int					ft_get_c(char *str, t_file *line);
int					*readxpm(t_file *file, char *str, char c);
int					addsprite(t_file *file, float x, float y);
float				distance(float x1, float y1, float x2, float y2);
void				windowmanager(t_file *file);
int					releaseinput(int i, t_file *file);
int					holdinput(int i, t_file *file);
int					try(t_file *file, int option);
int					get_text_colorn(t_file *file, float x,
						float current, int last);
int					get_text_colors(t_file *file, float x,
						float current, int last);
int					get_text_colore(t_file *file, float x,
						float current, int last);
int					get_text_colorw(t_file *file, float x,
						float current, int last);
void				setxiyi(t_file *file, float *xi, float *yi);
int					checkd(t_file *file, float interx[2], float intery[2]);
void				freefile(t_file *file);
int					collision(t_file *file, float x, float y);
void				hud(t_file *file);
void				updatehud(t_file *file, int option);
void				addscore(t_file *file);
void				initgun(t_file *file);
void				rendergun(t_file *file);
t_enemy				*newenemy(t_file *file, int i, int id);
t_enemy				*findbyid(t_file *file, int id);
void				enemygen(t_file *file, int i);
int					addenemy(t_file *file, float x, float angle);
void				moveall(t_file *file);
void				start_bmp(t_file *file);
void				smile(t_file *file);
void				calcorder(t_file *file, float angle);
void				calculateintersect(t_file *file, int i, float x, float y);
int					calcenemy(t_file *file, t_enemy *i, float x, float y);
int					*otherreadxpm(t_file *file, char *str, char c);
void				printfwall(t_file *file, float x, float y);
void				shootmanager(t_file *file);
int					enraycast(t_file *file, float x, float y, t_enemy *enemy);
void				playershot(t_file *file, t_enemy *enemy);
void				setaudio(t_file *file);
void				freeallfiles(t_file *file);
int					checkdouble(t_file *file, char c);
int					checkcub(char *map, char *option, int ac);
int					checkplayer(t_file *file, int i);
void				freeandout(t_file *file, char *str, char *print);

#endif
