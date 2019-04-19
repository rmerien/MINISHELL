/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 19:50:50 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/23 11:28:19 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int			exe_echo(t_env *env, char **av)
{
	int		j;
	char	linefeed;

	(void)env;
	linefeed = '\n';
	j = 1;
	if (av[j])
	{
		while (!ft_strcmp(av[j], "-n"))
		{
			linefeed = 0;
			j++;
		}
		while (av[j])
		{
			write(1, av[j], ft_strlen(av[j]));
			write(1, " ", 1);
			j += 1;
		}
	}
	write(1, &linefeed, 1);
	return (1);
}
