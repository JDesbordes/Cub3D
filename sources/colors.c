/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   colors.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/18 17:47:10 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 14:46:08 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cube.h"

int		ft_power(int nb, int power)
{
	int		res;

	res = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (nb == 0)
		return (0);
	while (power > 0)
	{
		res = res * nb;
		power--;
	}
	return (res);
}

int		ft_hexatoi(char *str, char *start)
{
	char	*hex;
	int		len;
	int		nb;
	int		i;
	int		j;

	free(start);
	hex = "0123456789abcdef";
	len = ft_strlen(str);
	nb = 0;
	i = 0;
	j = 0;
	while (--len >= 0)
	{
		while (hex[i] != str[len])
			i++;
		if (len == (int)ft_strlen(str) - 1)
			nb += i;
		else
			nb += i * ft_power(16, j);
		j++;
		i = 0;
	}
	free(str);
	return (nb);
}

int		quickcheck(char *color, char *start, int rgb[4], t_file *file)
{
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255
		|| rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
	{
		free(color);
		free(start);
		freeandout(file, NULL, "Color not in between 0 and 255");
	}
	return (ft_hexatoi(color, start));
}

int		ft_get_c(char *str, t_file *file)
{
	int		rgb[4];
	char	*start;
	char	*hex;
	char	*color;

	hex = "0123456789adcdef";
	start = str;
	if (!(color = malloc(sizeof(char) * 7)))
		return (0);
	color[6] = 0;
	rgb[0] = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	str++;
	rgb[1] = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	rgb[2] = ft_atoi(str + 1);
	color[0] = hex[rgb[0] / 16];
	color[1] = hex[rgb[0] % 16];
	color[2] = hex[rgb[1] / 16];
	color[3] = hex[rgb[1] % 16];
	color[4] = hex[rgb[2] / 16];
	color[5] = hex[rgb[2] % 16];
	return (quickcheck(color, start, rgb, file));
}
