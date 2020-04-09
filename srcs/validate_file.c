/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:28:38 by elindber          #+#    #+#             */
/*   Updated: 2019/12/11 19:53:17 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_fillit.h"

/*
** This function checks that every block is 4x4 and have only '.' '#' or '\n'.
*/

static int		validate_4x4_chars(char *tmns)
{
	int		i;
	int		line;
	int		topleft;

	i = 0;
	line = 0;
	topleft = 0;
	while (tmns[i])
	{
		if (tmns[i] == '\n' && tmns[i - 1] == '\n')
		{
			i++;
			topleft = i;
		}
		if (tmns[i] == '\n' && (tmns[i + 1] == '\n' || tmns[i + 1] == '\0')
			&& (i - line != 4 || i - topleft != 19))
			return (-1);
		if ((tmns[i] == '\n' && i - line != 4) || (tmns[i] != '\n' &&
			tmns[i] != '#' && tmns[i] != '.'))
			return (-1);
		if (tmns[i - 1] == '\n' && tmns[i] != '\n')
			line = i;
		i++;
	}
	return (0);
}

/*
** This functions checks that pieces are of right shape. Valid tetrimino has 6
** connections or 8 if it's a square-shape.
*/

static int		validate_pieces(char *tmns, int i, int topleft, int conn)
{
	while (tmns[i])
	{
		if (tmns[i] == '#' && tmns[i + 1] == '#')
			conn++;
		if (tmns[i] == '#' && tmns[i - 1] == '#')
			conn++;
		if (tmns[i] == '#' && i - topleft > 4 && i - topleft < 15 && tmns[i + 5] == '#')
			conn++;
		if (tmns[i] == '#' && i - topleft > 4 && i - topleft < 15 && tmns[i - 5] == '#')
			conn++;
		if ((tmns[i] == '#' && i - topleft > 14 && tmns[i - 5] == '#') ||
			(tmns[i] == '#' && i - topleft < 5 && tmns[i + 5] == '#'))
			conn++;
		if (tmns[i] == '\n' && (tmns[i + 1] == '\n' || tmns[i + 1] == '\0')
			&& conn != 6 && conn != 8)
			return (-1);
		if (tmns[i] == '\n' && tmns[i - 1] == '\n')
			topleft = i + 1;
		if (tmns[i] == '\n' && tmns[i - 1] == '\n')
			conn = 0;
		i++;
	}
	return (0);
}

/*
** First we call validate_pieces. If that passes, then we check that
** every 4x4 block has 4 #-characters and we transfomr them to letters
** starting from A.
*/

static int		validate_shape(char *tmns, int i)
{
	char	alpha;
	int		hash;

	alpha = 'A';
	hash = 0;
	if (validate_pieces(tmns, 0, 0, 0) < 0)
		return (-1);
	while (tmns[i])
	{
		if (tmns[i] == '#')
			hash++;
		if (tmns[i] == '#')
			tmns[i] = alpha;
		if (tmns[i] == '\n' && (tmns[i + 1] == '\n' || tmns[i + 1] == '\0')
			&& hash != 4)
			return (-1);
		if (tmns[i] == '\n' && tmns[i - 1] == '\n')
		{
			alpha++;
			hash = 0;
		}
		i++;
	}
	return (0);
}

/*
** We read the whole file at once, then we call for validation functions.
** After that we check that there are between 1-26 tetriminoes.
** Lastly (when all validations have passed) we call create_list to create
** a linked list of tetriminoes.
*/

int				validate_file(int fd, t_tetri **list)
{
	char		*file[MAX_FD];
	char		buff[BUFF_SIZE + 1];
	int			linecount;
	int			i;

	linecount = 0;
	i = -1;
	if (read(fd, buff, BUFF_SIZE) < 0)
		return (-1);
	file[fd] = buff;
	if ((validate_4x4_chars(file[fd]) < 0) || (validate_shape(file[fd], 0) < 0))
		return (-1);
	while (file[fd][++i])
		if (file[fd][i] == '\n')
			linecount++;
	if ((linecount < 4 || linecount > 129) || (linecount + 1) % 5 != 0)
		return (-1);
	if (!(create_list(file[fd], 0, list)))
		return (-1);
	return (1);
}
