/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 00:48:31 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/22 11:51:23 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static char		*ft_itoa(int n)
{
	int			len;
	char		*str;
	int			tmp;

	len = 0;
	tmp = n;
	while (tmp)
	{
		tmp /= 10;
		len += 1;
	}
	if (!(str = ft_strnew(len + 1)))
		return (0);
	str[len] = '\0';
	while (--len >= 0)
	{
		str[len] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}

static int		ft_getname(char *str, char **name, char **cont)
{
	int		i;
	int		len;
	int		c;

	i = 0;
	c = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i += 1;
	if (!(*name = ft_strnew(i + 1)))
		return (1);
	if (!(*cont = ft_strnew(len - i)))
		return (1);
	while (*str && *str != '=')
		(*name)[c++] = *str++;
	(*name)[c] = 0;
	c = 0;
	while (*++str)
		(*cont)[c++] = *str;
	(*cont)[c] = 0;
	return (0);
}

static int		delnorme(int norme, char **a, char **b, char **c)
{
	ft_strdel(a);
	ft_strdel(b);
	if (norme)
		ft_strdel(c);
	return (0);
}

/*
** tab[0] ; name of the variable
** tab[1] : content of the variable
** tab[2] : temporary variable
*/

int				split_env(t_env **env, char *const *strenv)
{
	char	*tab[3];
	t_env	*save;
	int		useless_but_lifesaving_variable;

	useless_but_lifesaving_variable = 0;
	while (*strenv)
	{
		tab[0] = NULL;
		tab[1] = NULL;
		if (ft_getname(*strenv, &tab[0], &tab[1]))
			return (1);
		if (!ft_strcmp(tab[0], "SHLVL"))
		{
			ft_addvar(env, tab[0], (tab[2] = ft_itoa(ft_atoi(tab[1]) + 1)));
			delnorme(1, &tab[0], &tab[1], &tab[2]);
		}
		else if (ft_addvar(env, tab[0], tab[1]))
			return (delnorme(0, &tab[0], &tab[1], NULL) + (free_env(*env)));
		if (useless_but_lifesaving_variable++ == 0)
			save = *env;
		delnorme(0, &tab[0], &tab[1], NULL);
		strenv += 1;
	}
	*env = save;
	return (0);
}
