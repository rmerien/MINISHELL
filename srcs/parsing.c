/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */ /*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2019/01/14 06:46:40 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/24 08:45:49 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_valid_command(char *str, const char *str2)
{
	int		i;

	i = -1;
	while (str[++i] && i < 9)
		str[i] = ((64 < str[i] && str[i] < 91) ? str[i] + 32 : str[i]);
	i = 0;
	while (str[i] == str2[i] && str[i])
		i += 1;
	return (str[i] == str2[i] ? 1 : 0);
}

int			parser(t_env **env, char **av)
{
	char	*tmp;

	if (!av[0] || !av)
		return (0);
	if (ft_valid_command(av[0], "echo"))
		return (exe_echo(*env, av));
	else if (!ft_strcmp(av[0], "exit"))
		exe_exit(*env, av);
	else if (ft_valid_command(av[0], "cd"))
		return (exe_cd(*env, av));
	else if (ft_valid_command(av[0], "env"))
		return (exe_env(*env, av));
	else if (ft_valid_command(av[0], "setenv"))
		return (exe_setenv(*env, av));
	else if (ft_valid_command(av[0], "unsetenv"))
		return (exe_unsetenv(env, av));
	else if (!ft_strchr(av[0], '/'))
	{
		tmp = find_content(*env, "PATH");
		av[0] = search_path_var(av[0], tmp);
	}
	exe_file(av, *env);
	return (42);
}
