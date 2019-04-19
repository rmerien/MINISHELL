/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 05:24:25 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/24 08:46:16 by rmerien          ###   ########.fr       */
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
