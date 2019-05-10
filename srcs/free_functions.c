/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 05:24:25 by rmerien           #+#    #+#             */
/*   Updated: 2019/05/02 20:21:12 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		ft_strdel(&tmp->name);
		ft_strdel(&tmp->content);
	}
	return (3);
}

int		free_tab(char **argv)
{
	int		i;

	i = 0;
	while (argv && argv[i])
		ft_strdel(&(argv[i++]));
	if (argv)
	{
		free(argv);
		argv = NULL;
	}
	return (1);
}

int			free_all(t_env *env, char **av)
{
	(void)env;
	free_tab(av);
//	free_env(env);
	return (3);
}
