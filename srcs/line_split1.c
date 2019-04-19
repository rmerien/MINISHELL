/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:12:07 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/27 14:15:15 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int			ft_splitline(char ***av, char *line, t_env *env, int count)
{
	int		pos;
	int		ac;
	t_line	info;

	pos = 0;
	ac = 0;
	while (count--)
	{
		while (line[pos] == ' ' || line[pos] == '\t')
			pos += 1;
		info = ft_argsize(&line[pos], env);
		if (!((*av)[ac] = ft_strnew(info.lenmal + 1)))
			return (1);
		fill_arg(&line[pos], env, (*av)[ac++]);
		(*av)[ac] = NULL;
		pos += info.pos;
	}
	return (0);
}

/*
** Function used to join multiple lines in case of an unmatched " or '.
*/

int			fk_the_norm(char **line)
{
	char	*tmp1;
	char	*tmp2;
	int		rd_ret;

	tmp1 = NULL;
	tmp2 = NULL;
	write(1, "> ", 2);
	if ((rd_ret = get_line(&tmp2)) < 0)
		return (rd_ret);
	tmp1 = *line;
	if (!(*line = ft_strjoin(*line, tmp2)))
		return (3);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (5);
}

/*
** av = arguments
** line = get_line
** argc = argument count
** rd_ret = secure get_line
*/

int			ft_getargs(char ***argv, t_env *env)
{
	char	*line;
	int		argc;
	int		rd_ret;

	line = NULL;
	*argv = NULL;
	if ((rd_ret = get_line(&line)) < 0)
		return (1);
	else if (rd_ret == 0)
		exe_exit(env, *argv);
	while ((argc = ft_argcount(line)) < 0)
		if ((rd_ret = fk_the_norm(&line)) < 5)
			return (rd_ret);
	line[ft_strlen(line) - 1] = 0;
	if (!((*argv) = (char **)ft_memalloc(sizeof(char *) * (argc + 1))))
		return (4);
	if (ft_splitline(argv, line, env, argc))
		return (5);
	ft_strdel(&line);
	return (0);
}
