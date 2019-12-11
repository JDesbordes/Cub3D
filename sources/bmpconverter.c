/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bmpconverter.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/04 12:06:51 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 17:46:21 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/cube.h"

void	bitmap_image(t_file *file, int fd, t_header2 bih)
{
	int				x;
	int				y;
	int				ble;
	unsigned char	color[3];

	write(fd, &bih, sizeof(bih));
	y = file->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < file->width)
		{
			ble = file->imgdata[x + y * file->width];
			color[0] = ble % 256;
			ble /= 256;
			color[1] = ble % 256;
			ble /= 256;
			color[2] = ble % 256;
			write(fd, &color, sizeof(color));
			x++;
		}
		y--;
	}
}

void	save_bitmap(const char *filename, t_file *file)
{
	int			fd;
	t_header	bfh;
	t_header2	bih;

	ft_memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size = file->width * file->height * 4 + 54;
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.offset_bits = 0;
	bih.size_header = sizeof(bih);
	bih.width = file->width;
	bih.height = file->height;
	bih.planes = 1;
	bih.bit_count = 24;
	bih.compression = 0;
	bih.image_size = file->width * file->height * 4 + 54;
	bih.ppm_x = 2;
	bih.ppm_y = 2;
	bih.clr_used = 0;
	bih.clr_important = 0;
	close(open(filename, O_WRONLY | O_CREAT));
	fd = open(filename, O_RDWR);
	write(fd, &bfh, 14);
	bitmap_image(file, fd, bih);
	close(fd);
}

void	smile(t_file *file)
{
	int		bits;
	int		sizeline;
	int		end;

	file->img = mlx_new_image(MLX, file->width, file->height);
	file->imgdata = (int *)mlx_get_data_addr(file->img, &bits, &sizeline, &end);
	file->setup = 1;
	hud(file);
	raycastgen(file);
	save_bitmap("cube.bmp", file);
}

void	printwall(t_file *file, float x, float y, int j)
{
	if (file->side)
	{
		if (PLAYER.y > y)
			file->imgdata[file->ray + (j * file->width)] = get_text_colorn(file,
				x, j - file->drawstart, file->drawend - file->drawstart);
		else
			file->imgdata[file->ray + (j * file->width)] = get_text_colors(file,
				x, j - file->drawstart, file->drawend - file->drawstart);
	}
	else
	{
		if (PLAYER.x > x)
			file->imgdata[file->ray + (j * file->width)] = get_text_colorw(file,
				y, j - file->drawstart, file->drawend - file->drawstart);
		else
			file->imgdata[file->ray + (j * file->width)] = get_text_colore(file,
				y, j - file->drawstart, file->drawend - file->drawstart);
	}
}

void	printfwall(t_file *file, float x, float y)
{
	float	lh;
	int		j;
	float	temp;
	float	dist;

	file->hit = 1;
	temp = file->rayangle;
	file->rayangle = PLAYER.rotation - file->rayangle;
	file->rayangle *= M_PI / 180;
	file->dist = distance(PLAYER.x, PLAYER.y, x, y);
	dist = file->dist * cos(file->rayangle);
	lh = (int)(1.0 * (file->height / dist));
	file->drawstart = -lh / 1 + file->height / 2;
	file->drawend = lh / 1 + file->height / 2;
	j = 0;
	while (j < (file->height - file->height / 8))
	{
		if (j > file->drawstart && j < file->drawend)
			printwall(file, x, y, j);
		else
			file->imgdata[file->ray + (j * file->width)] =
				j > file->height / 2 ? MAP.ftext : MAP.ctext;
		j++;
	}
	calcorder(file, temp);
}
