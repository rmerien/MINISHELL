/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 20:40:24 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/24 08:55:01 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static inline void	norme(t_env **a, t_env ***b, int *c)
{
	*c += 1;
	(*a) = (**b);
	(**b) = (**b)->next;
}

int					exe_unsetenv(t_env **env, char **av)
{
	t_env	*prev_env;
	t_env	*start_env;
	int		i;
	int		count;

	i = 0;
	start_env = (*env);
	while (av[++i])
	{
		count = 0;
		while ((*env) && ft_strcmp((*env)->name, av[i]))
			norme(&prev_env, &env, &count);
		if ((*env))
		{
			if (count)
				prev_env->next = (*env)->next;
			else
				start_env = (*env)->next;
			ft_strdel(&(*env)->name);
			ft_strdel(&(*env)->content);
			free((*env));
		}
		(*env) = start_env;
	}
	return (0);
}
