/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getndraw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 10:50:09 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/01 10:53:45 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

char			*get_state_info(int state)
{
	if (state == 0)
		return ("THINK    ");
	else if (state == 1)
		return ("REST     ");
	else if (state == 2)
		return ("EAT      ");
	else if (state == 3)
		return ("WANT EAT ");
	else
		return ("ERROR");
}

char			*get_state_face(int state)
{
	if (state == 0)
		return ("./imgs/facethink.txt");
	else if (state == 1)
		return ("./imgs/facerest.txt");
	else if (state == 2)
		return ("./imgs/faceeat.txt");
	else if (state == 3)
		return ("./imgs/facestarve.txt");
	else
		return ("ERROR");
}

void			draw_stick(WINDOW *philo, int maxy, int maxx, int index)
{
	char	*ret;
	int		fd;
	int		i;

	i = 6;
	fd = open("./imgs/Lstick.txt", O_RDONLY);
	wattrset(philo, COLOR_PAIR(3));
	if (fd != -1)
		while (get_next_line(fd, &ret) != 0)
			if (PHI[index].stick_right == 1)
				mvwprintw(philo, ++i, maxy - 6, "%s", ret);
	i = 6;
	close(fd);
	fd = open("./imgs/Rstick.txt", O_RDONLY);
	if (fd != -1)
		while (get_next_line(fd, &ret) != 0)
			if (PHI[index].stick_left == 1)
				mvwprintw(philo, ++i, 1, "%s", ret);
	close(fd);
}

void			draw_face(WINDOW *philo, int maxy, int maxx, char *path)
{
	char	*ret;
	int		fd;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd != -1)
		while (get_next_line(fd, &ret) != 0)
			mvwprintw(philo, ++i, (maxy / 2) - (ft_strlen(ret) / 2), "%s", ret);
	close(fd);
}
