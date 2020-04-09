/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:00:32 by elindber          #+#    #+#             */
/*   Updated: 2020/01/02 17:51:45 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_fillit.h"

int		main(int ac, char **av)
{
	int		fd;
	int		ret;
	t_tetri	*list;

	if (ac != 2)
	{
		ft_putstr_fd("usage: ", STDERR_FILENO);
		ft_putstr_fd(av[0], STDERR_FILENO);
		ft_putstr_fd(" [input_file]\n", STDERR_FILENO);
		return (-1);
	}
	if (!(fd = open(av[1], O_RDONLY)))
	{
		ft_putstr_fd("open error\n", 2);
		return (-1);
	}
	if ((ret = validate_file(fd, &list)) < 0)
	{
		ft_putstr("error\n");
		return (-1);
	}
	create_map(list, map_size(count_nodes(list) * 4));
	close(fd);
	return (0);
}
