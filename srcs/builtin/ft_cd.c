/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 07:00:04 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/27 14:49:01 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

static int	ft_special_occ(t_env *env, int occ)
{
	char	path[PATH_MAX + 1];
	char	*new_dir;

	new_dir = NULL;
	if (!occ)
	{
		if (!(new_dir = find_content(env, "HOME")))
			return (0);
	}
	else if (!(new_dir = find_content(env, "OLDPWD")))
		new_dir = ft_strdup("..");
	getcwd(path, PATH_MAX);
	modify_var(&env, "OLDPWD", path);
	if (chdir(new_dir) == -1)
	{
		write(2, "cd: permission denied: ", 22);
		ft_putendl_fd(new_dir, 2);
	}
	modify_var(&env, "PWD", new_dir);
	ft_strdel(&new_dir);
	return (0);
}

static int	valid_arg(t_env *env, char **av)
{
	char	path[PATH_MAX + 1];

	getcwd(path, PATH_MAX);
	if (chdir(av[1]) == -1)
	{
		write(2, "cd: permission denied: ", 22);
		ft_putendl_fd(av[1], 2);
	}
	else
	{
		modify_var(&env, "OLDPWD", path);
		getcwd(path, PATH_MAX);
		modify_var(&env, "PWD", path);
	}
	return (0);
}

int			exe_cd(t_env *env, char **av)
{
	struct stat buf;

	if (av[1] && av[2])
		write(2, "cd: too many arguments\n", 23);
	else if (!av[1] || !ft_strcmp(av[1], "--"))
		ft_special_occ(env, 0);
	else if (!ft_strcmp(av[1], "-"))
		ft_special_occ(env, 1);
	else if ((stat(av[1], &buf) == -1))
		write(2, "cd: no such file or directory: ", 30)
			? ft_putendl_fd(av[1], 2) : 0;
	else if (S_ISDIR(buf.st_mode))
		valid_arg(env, av);
	else
		write(2, "cd: not a directory: ", 21) ? ft_putendl_fd(av[1], 2) : 0;
	return (1);
}
