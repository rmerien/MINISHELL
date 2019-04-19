/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:07:00 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/28 14:05:34 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <stdlib.h>

static char		*ft_delnorme(int norme, char **a, char **b, char **c)
{
	ft_strdel(a);
	if (norme)
		ft_strdel(b);
	ft_strdel(c);
	return (*b);
}

static void		ft_mercilanorme(char **a, char **b, char c[1024], DIR *d)
{
	*a = ft_strjoin(*b, "/");
	ft_strdel(b);
	*b = ft_strjoin(*a, c);
	closedir(d);
}

char			*search_path_var(char *file, char *path)
{
	DIR				*d;
	struct dirent	*ent;
	char			*(tmp[2]);
	int				i;

	i = 0;
	if (path)
		while (path[i] && path)
		{
			if ((tmp[0] = ft_strsub(&path[i], 0, ft_lentoc(&path[i], ':'))))
				if ((d = opendir(tmp[0])))
				{
					while ((ent = readdir(d)))
						if (!ft_strcmp(ent->d_name, file))
						{
							ft_mercilanorme(&tmp[1], &tmp[0], ent->d_name, d);
							ft_delnorme(1, &tmp[1], &file, &path);
							return (tmp[0]);
						}
					closedir(d);
				}
			norme_v3(&tmp[0], path, &i);
		}
	norme_v2(&path, file);
	return (file);
}

static int		ft_shrink(char ***env, t_env *list)
{
	t_env	*save;
	int		len;
	char	*tmp;
	int		i;

	save = list;
	len = 0;
	i = 0;
	while (list && ++len)
		list = list->next;
	list = save;
	if (!((*env) = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		return (1);
	while (len--)
	{
		tmp = ft_strjoin(list->name, "=");
		(*env)[i] = ft_strjoin(tmp, list->content);
		ft_strdel(&tmp);
		if (!(*env)[i])
			return (free_tab(*env));
		(*env)[++i] = NULL;
		list = list->next;
	}
	list = save;
	return (0);
}

int				exe_file(char **av, t_env *list)
{
	pid_t	pid;
	char	**env;
	int		check;

	if (!av[0])
		return (0);
	env = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (ft_shrink(&env, list))
			return (1);
		execve(av[0], &av[0], (char *const *)env);
		free_tab(env);
		exit(0);
	}
	if (pid > 0)
		wait(&check);
	return (0);
}
