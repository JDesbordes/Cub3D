/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   readmap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/14 15:19:33 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 14:44:21 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cube.h"

int		get_r(t_file *file, char *line)
{
	int i;
	int temp;

	i = 0;
	temp = ft_atoi(ft_strchr(line, ' '));
	if (file->width != 0 || (temp != file->oldwidth && file->oldwidth != 0))
		return (0);
	file->width = temp;
	while (!(ft_isdigit(line[i])))
		i++;
	while (ft_isdigit(line[i]))
		i++;
	temp = ft_atoi(line + i);
	if (file->height != 0 || (temp != file->oldheight && file->oldheight != 0))
		return (0);
	file->height = temp;
	if (file->width > SCREENWIDTH / 2)
		file->width = SCREENWIDTH / 2;
	if (file->height > SCREENHEIGHT / 2)
		file->height = SCREENHEIGHT / 2;
	file->oldheight = file->height;
	file->oldwidth = file->width;
	return (1);
}

char	*rspace(char *line)
{
	char	*nline;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			j++;
		i++;
	}
	nline = calloc(1, i - j + 1);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			nline[j] = line[i];
			j++;
		}
		i++;
	}
	return (nline);
}

int		parsemap(t_file *file, char *line)
{
	if (line[0] == '1' || line[0] == '0' || line[0] == '2' || line[0] == 'N'
	|| line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
	{
		MAP.maplines++;
		line = rspace(line);
		if (!MAP.size)
			MAP.size = ft_strlen(line);
		else if (MAP.size != (int)ft_strlen(line))
			return (0);
		MAP.layout = ft_strjoinrem(MAP.layout, line);
		free(line);
	}
	else if (MAP.size || (line[0] != '\n' && line[0] != '\0'))
		return (0);
	return (1);
}

int		readmap2(t_file *file, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && !MAP.size)
		MAP.ntext = otherreadxpm(file, ft_strrchr(line, ' ') + 1, 'N');
	else if (!ft_strncmp(line, "WE", 2) && !MAP.size)
		MAP.wtext = otherreadxpm(file, ft_strrchr(line, ' ') + 1, 'W');
	else if (!ft_strncmp(line, "EA", 2) && !MAP.size)
		MAP.etext = otherreadxpm(file, ft_strrchr(line, ' ') + 1, 'E');
	else if (!ft_strncmp(line, "S ", 2) && !MAP.size)
		MAP.sptext = readxpm(file, ft_strrchr(line, ' ') + 1, 'P');
	else if (!ft_strncmp(line, "A1", 2) && !MAP.size)
		MAP.atext = readxpm(file, ft_strrchr(line, ' ') + 1, 'A');
	else if (!ft_strncmp(line, "A2", 2) && !MAP.size)
		MAP.a2text = readxpm(file, ft_strrchr(line, ' ') + 1, 'B');
	else if (!ft_strncmp(line, "A3", 2) && !MAP.size)
		MAP.a3text = readxpm(file, ft_strrchr(line, ' ') + 1, 'C');
	else if (!ft_strncmp(line, "F ", 2) && MAP.ftext == -1 && !MAP.size)
		MAP.ftext = ft_get_c(ft_strtrimr(line + 2, " "), file);
	else if (!ft_strncmp(line, "C ", 2) && MAP.ctext == -1 && !MAP.size)
		MAP.ctext = ft_get_c(ft_strtrimr(line + 2, " "), file);
	else if (!ft_strncmp(line, "NL", 2) && !MAP.size && !MAP.nextlevel)
		MAP.nextlevel = ft_strtrimr(line + 2, " ");
	else if (parsemap(file, line))
		return (1);
	else
		return (-1);
	return (1);
}

void	readmap(t_file *file, char *map)
{
	int		fd;
	char	*line;

	mapinit(file);
	if ((fd = open(map, 0)) < 0)
		freeandout(file, NULL, "wrong path to .cub");
	while (get_next_line(fd, &line))
	{
		if (!ft_strncmp(line, "R ", 2))
		{
			if (!get_r(file, line))
				freeandout(file, line, "change or error in res");
		}
		else if (!ft_strncmp(line, "SO", 2) && !MAP.size)
			MAP.stext = otherreadxpm(file, ft_strrchr(line, ' ') + 1, 'S');
		else if (readmap2(file, line) <= 0)
			freeandout(file, line, "Parsing error\n");
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	addscore(file);
}
