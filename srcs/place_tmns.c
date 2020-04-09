/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_tmns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:40:24 by elindber          #+#    #+#             */
/*   Updated: 2019/12/11 19:56:45 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_fillit.h"

/*
** This function places a piece to the map. It first puts the first letter
** and then the three others in the while loop  by using the data of relative
** coordinates.
*/

static void	place_piece(t_tetri *list, t_map *map, int y, int x)
{
	int		c;

	c = 0;
	map->dots[y][x] = list->alpha;
	while (c < 3)
	{
		map->dots[y + list->rltv[c][0]][x + list->rltv[c][1]] = list->alpha;
		c++;
	}
}

/*
** Finally, when the solution is found, we print it on the standard output and
** then we call free_map to free the memory so there won't be any memory leaks.
*/

static int	print_map(t_map *map, int y)
{
	while (map->dots[y] != NULL)
	{
		ft_putstr(map->dots[y]);
		ft_putchar('\n');
		y++;
	}
	free_map(map);
	return (1);
}

/*
** When current piece fits but the next doesn't, this function removes the
** current piece from the map It only removes the letters that are send to
** it (abc).
*/

static void	remove_piece(t_map *map, char alpha)
{
	int		y;
	int		x;

	y = 0;
	while (map->dots[y])
	{
		x = 0;
		while (map->dots[y][x])
		{
			if (map->dots[y][x] == alpha)
				map->dots[y][x] = '.';
			x++;
		}
		y++;
	}
}

/*
** This functions checks whether the piece fit's to the curren location
** on the map. It check's that every cordinate needed is free '.' and the
** relative cordinate spots don't go over the map.
*/

static int	check_fit(t_tetri *list, t_map *map, int y, int x)
{
	int		c;
	int		r;

	c = 0;
	r = 0;
	if (map->dots[y][x] != '.')
		return (0);
	while (c < 3)
	{
		if (list->rltv[c][0] + y >= map->size ||
			list->rltv[c][1] + x > map->size || list->rltv[c][1] + x < 0)
			break ;
		if (map->dots[list->rltv[c][0] + y][list->rltv[c][1] + x] == '.')
			r++;
		c++;
	}
	return (r == 3);
}

/*
** This function first checks where current tetrimino fits and then places it
** to the map (place_piece). After that it call's itself recursively with
** next tetrimino. If the next tetrimino doesn't fit, we remove the current
** tetrimino (remove_piece). If the current tetrimino doesn't fit anywhere
** in the map, this function returns 0 to the create_map function which then
** creates a bigger map If we get thet to end of list (list == NULL) then the
** solution is found and recursion stops.
*/

int			place_tmns(t_tetri *list, t_map *map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (list == NULL)
		return (print_map(map, 0));
	while (map->dots[y] != NULL)
	{
		if (check_fit(list, map, y, x))
		{
			place_piece(list, map, y, x);
			if (place_tmns(list->next, map))
				return (1);
			remove_piece(map, list->alpha);
		}
		x++;
		if (map->dots[y][x] == '\0')
		{
			y++;
			x = 0;
		}
	}
	return (0);
}
