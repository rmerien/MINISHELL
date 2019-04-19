/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 05:19:52 by rmerien           #+#    #+#             */
/*   Updated: 2019/04/04 15:55:42 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void		exe_exit(t_env *env, char **av)
{
	int		ret;

	ret = 0;
	if (av)
	{
		(void)env;
		ret = 0;
		if (av[0])
			if (av[1])
			{
				if (av[2])
				{
					write(2, "exit: too many arguments\n", 25);
					return ;
				}
				else
					ret = ft_atoi(av[1]);
			}
		free_tab(av);
	}
	write(1, "exit\n", 5);
	exit(ret);
}
