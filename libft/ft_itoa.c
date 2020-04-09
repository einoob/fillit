/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elindber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:59:16 by elindber          #+#    #+#             */
/*   Updated: 2019/11/12 18:31:29 by elindber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrcount(int n)
{
	long	k;
	size_t	i;

	k = n;
	i = 0;
	if (k < 0)
		k = k * -1;
	if (k == 0)
		i = 1;
	while (k > 0)
	{
		i++;
		k = k / 10;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	size_t	c;
	long	k;
	char	*str;

	c = ft_nbrcount(n);
	k = n;
	if (k < 0)
	{
		if (!(str = ft_strnew(c + 1)))
			return (NULL);
		str[0] = '-';
		k = k * -1;
	}
	else if (!(str = ft_strnew(c--)))
		return (NULL);
	if (k == 0)
		str[c] = '0';
	while (k > 0)
	{
		str[c] = '0' + k % 10;
		k = k / 10;
		c--;
	}
	return (str);
}
