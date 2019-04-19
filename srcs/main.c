/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 22:26:30 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/24 09:16:46 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <sys/syslimits.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <time.h>
#include "minishell.h"

int			main(const int argc, const char **argv, char **envir)
{
	char	path[PATH_MAX + 1];
	t_env	*env;
	char	**av;

	(void)argv[argc];
	env = NULL;
	if (!*envir)
	{
		if (basic_env(&env))
			return (4);
	}
	else if (split_env(&env, envir))
		return (4);
	av = NULL;
	while (1)
	{
		free_tab(av);
		if ((getcwd(path, PATH_MAX)))
		{
			if (!write_prompt(path) && !ft_getargs(&av, env))
				parser(&env, av);
		}
		else
			return (free_all(env, av));
	}
}
