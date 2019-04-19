/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 20:40:24 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/22 11:48:04 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static inline int	ft_isdigit(int c)
{
	return (47 < c && c < 58);
}

static inline int	ft_isalpha(char c)
{
	return ((64 < c && c < 91) || (96 < c && c < 123));
}

static inline int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int					exe_setenv(t_env *env, char **av)
{
	int		i;

	if (!av[1] || !av[2])
		return (write(2, "setenv: Too few arguments.\n", 27));
	if (av[3])
		return (write(2, "setenv: Too many arguments.\n", 28));
	i = 0;
	if (!(ft_isalpha(av[1][0])))
	{
		return (write(2,
				"setenv: Variable name must begin with a letter.\n", 50));
	}
	while (av[1][i])
	{
		if (!(ft_isalnum(av[1][i++])))
			return (write(2, "setenv: Variable name must contain only"
				" alphanumeric characters.\n", 65));
	}
	modify_var(&env, av[1], av[2]);
	return (0);
}
