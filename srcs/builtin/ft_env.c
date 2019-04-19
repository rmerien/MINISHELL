/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 04:58:55 by rmerien           #+#    #+#             */
/*   Updated: 2019/04/19 11:05:19 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_error(void)
{
	write(2, "env: too many arguments\n", 24);
	return (1);
}

int			exe_env(t_env *env, char **av)
{
	int			x;
	int			y;

	x = 0;
	if (av[1])
	{
		return (ft_error());
		while (av[++x] && av[x][0] == '-')
		{
			y = 0;
			while (av[x][++y])
				if (av[x][y] != 'i')
				{
					write(2, "env: illegal option -- ", 23);
					write(2, &av[x][y], 1);
					return (write(2, "\nusage: env [-i] [argument ...]\n", 32));
				}
		}
	}
	else
		while (env)
		{
			write(1, env->name, ft_strlen(env->name));
			write(1, "=", 1);
			ft_putendl_fd(env->content, 1);
			env = env->next;
		}
	return (1);
}
