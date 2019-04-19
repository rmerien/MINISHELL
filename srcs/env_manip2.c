/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manip2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 05:06:24 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/21 15:31:05 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int			basic_env(t_env **env)
{
	char	path[PATH_MAX];
	t_env	*save;

	if (!getcwd(path, PATH_MAX))
		return (1);
	if (ft_addvar(env, "PWD", path))
		return (free_env(*env));
	save = *env;
	if (ft_addvar(env, "SHLVL", "1"))
		return (free_env(*env));
	*env = save;
	return (0);
}

int			ft_addvar(t_env **env, char *name, char *content)
{
	t_env	*new_var;

	if (!(new_var = (t_env *)ft_memalloc(sizeof(t_env))))
		return (1);
	new_var->next = NULL;
	if (*env)
	{
		while ((*env)->next)
			*env = (*env)->next;
		(*env)->next = new_var;
	}
	else
		*env = new_var;
	if (!(new_var->name = ft_strdup(name)))
		return (1);
	if (!(new_var->content = ft_strdup(content)))
		return (1);
	return (0);
}

char		*find_content(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strcmp(tmp->name, var_name))
		tmp = tmp->next;
	return (tmp ? ft_strdup(tmp->content) : NULL);
}

int			modify_var(t_env **env, char *name, char *content)
{
	t_env	*save;

	save = *env;
	while ((*env) && (*env)->next && ft_strcmp((*env)->name, name))
		(*env) = (*env)->next;
	if ((*env)->next && !ft_strcmp((*env)->name, name))
	{
		ft_strdel(&(*env)->content);
		(*env)->content = ft_strdup(content);
	}
	else
		ft_addvar(env, name, content);
	*env = save;
	return (0);
}
