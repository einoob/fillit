/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmns_solver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:21:54 by elindber          #+#    #+#             */
/*   Updated: 2019/12/11 19:54:19 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_fillit.h"

/*
** This functions looks for the first alphabet in the block.
** When that is found we take it's cordinates (x, y) and which letter (alpha)
** it is and send them to linked list node.
*/

static void	set_xy_alpha(char *tmns, int i, t_tetri **list)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (!(ft_isalpha(tmns[i])))
	{
		if (tmns[i] == '\n')
		{
			x = -1;
			y++;
		}
		x++;
		i++;
	}
	(*list)->x = x;
	(*list)->y = y;
	(*list)->alpha = tmns[i];
}

/*
** This function calculates the relative cordinates of three other letters
** and sends the data to a int-array (list->rltv[][]) in the linked list node.
*/

static void	set_relative_xy(t_tetri **list, int count)
{
	int		x;
	int		y;
	int		relative_xy;

	x = (*list)->x + 1;
	y = (*list)->y;
	relative_xy = 0;
	while (count < 3)
	{
		if (ft_isalpha((*list)->block[y][x]))
		{
			(*list)->rltv[count][relative_xy] = y - (*list)->y;
			relative_xy++;
			(*list)->rltv[count][relative_xy] = x - (*list)->x;
			relative_xy = 0;
			count++;
		}
		x++;
		if ((*list)->block[y][x] == '\0')
		{
			y++;
			x = 0;
		}
	}
}

/*
** This function creates the linked list of tetriminoes. We send the
** array of whole file to this function. We allocate memory for every
** block and then we allocate and copy data by using ft_strsub.
** Then we call two functions to set more data into the node and after
** that we move to the next node recuriscevely. When we are in the end of
** the array, we go back to the main function.
*/

int			create_list(char *tmns, int i, t_tetri **list)
{
	int			line;

	if (tmns[i] == '\0')
		return (1);
	if (!(*list = malloc(sizeof(t_tetri))))
		return (-1);
	if (!((*list)->block = (char**)malloc(sizeof(char*) * 5)))
		return (-1);
	line = 0;
	while (line < 4)
	{
		if (!((*list)->block[line] = ft_strsub(tmns, i, 4)))
			return (-1);
		i = i + 5;
		line++;
	}
	(*list)->block[line] = NULL;
	i++;
	set_xy_alpha(tmns, i - 21, list);
	set_relative_xy(list, 0);
	create_list(tmns, i, &(*list)->next);
	return (1);
}
