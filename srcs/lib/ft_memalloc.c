/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:58:19 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/04 16:04:32 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *tb;

	tb = b;
	while (len--)
		*tb++ = (unsigned char)c;
	return (b);
}

void		*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = malloc(size)))
		return (0);
	return (ft_memset(mem, 0, size));
}
