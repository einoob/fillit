/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 18:48:00 by elindber          #+#    #+#             */
/*   Updated: 2019/12/11 19:55:26 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_fillit.h"

/*
** This function frees the map when we have to grow it's size and als after the
** solution so that we don't have memory leaks.
*/

void		free_map(t_map *map)
{
	int	y;

	y = 0;
	while (map->dots[y])
		y++;
	while (y != -1)
	{
		ft_strdel(&map->dots[y]);
		y--;
	}
	free(map->dots);
	map->dots = NULL;
	free(map);
}

/*
** This function counts the size of the smallest possible square and returns
** it to the create_map functions which then creates the map of that size.
*/

int			map_size(int size)
{
	int		count;

	count = 2;
	while (count * count < size)
		count++;
	return (count);
}

/*
** We get the int size from map_size function. Then we allocate memory for the
** map itself. Then we allocate memory for the square (map->dots) line by line.
** After that we call place_tmns which solves the square. If it can't solve the
** square we call create_map again but with a one bigger square size.
*/

int			create_map(t_tetri *list, int size)
{
	int		y;
	t_map	*map;

	y = 0;
	if (!(map = malloc(sizeof(t_map))))
		return (-1);
	if (!(map->dots = (char**)malloc(sizeof(char*) * (size + 1))))
		return (-1);
	map->size = size;
	while (y < size)
	{
		if (!(map->dots[y] = ft_memset(ft_strnew(size), '.', size)))
			return (-1);
		y++;
	}
	map->dots[y] = NULL;
	if (!place_tmns(list, map))
	{
		free_map(map);
		create_map(list, size + 1);
	}
	return (0);
}

/*
** This function counts the amount of tetriminoes so that we can calculate
** the size of smallest possible square for the pieces.
*/

int			count_nodes(t_tetri *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}
