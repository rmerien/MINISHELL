/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 08:39:18 by rmerien           #+#    #+#             */
/*   Updated: 2019/05/02 09:55:33 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_insub(char c, char sub)
{
	return (!(c == ' ' || c == '\t') || sub);
}

char		*ft_varname(char *str)
{
	int		size;
	char	*var;

	size = 0;
	if ((64 < str[size] && str[size] < 91)
			|| (96 < str[size] && str[size] < 123))
	{
		size += 1;
		while ((47 < str[size] && str[size] < 48)
				|| (64 < str[size] && str[size] < 91)
				|| (96 < str[size] && str[size] < 123))
		{
			size += 1;
		}
	}
	if (!(var = ft_strnew(size)))
		return (0);
	while (size-- > 0)
		var[size] = str[size];
	return (var);
}

void		norme_v2(char **a, char *b)
{
	ft_strdel(a);
	write(2, "minishell: command not found: ", 30);
	ft_putendl_fd(b, 2);
}

void		norme_v3(char **a, char *b, int *c)
{
	ft_strdel(a);
	*c += ft_lentoc(&b[*c], ':');
	*c += (b[*c] ? 1 : 0);
}

int		ft_uselessinit(int *c, int *a, char *b)
{
	*a = 0;
	*c = 0;
	*b = 0;
	return (0);
}
