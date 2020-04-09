/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_fillit.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:46:55 by elindber          #+#    #+#             */
/*   Updated: 2019/12/11 18:02:29 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_FILLIT_H
# define HEADER_FILLIT_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define MAX_FD 10
# define BUFF_SIZE 634

typedef struct		s_tetri
{
	char			**block;
	char			alpha;
	int				x;
	int				y;
	int				rltv[3][2];
	struct s_tetri	*next;

}					t_tetri;

typedef struct		s_map
{
	int				size;
	char			**dots;

}					t_map;

int					validate_file(int fd, t_tetri **list);
int					create_list(char *tmns, int i, t_tetri **list);
int					create_map(t_tetri *list, int size);
int					place_tmns(t_tetri *list, t_map *map);
int					count_nodes(t_tetri *list);
int					map_size(int size);
void				free_map(t_map *map);

#endif
