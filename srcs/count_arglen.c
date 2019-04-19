/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arglen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:43:06 by rmerien           #+#    #+#             */
/*   Updated: 2019/04/02 16:56:10 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			spcl_len(char c, char sub)
{
	char	final;
	char	final2;

	final = 0;
	final2 = 0;
	if (sub)
	{
		final = (c == 'a' && !final) ? 7 : final;
		final = (c == 'b' && !final) ? 8 : final;
		final = (c == 'e' && !final) ? 27 : final;
		final = (c == 'f' && !final) ? 12 : final;
		final = (c == 'n' && !final) ? 10 : final;
		final = (c == 'r' && !final) ? 13 : final;
		final = (c == 't' && !final) ? 9 : final;
		final = (c == 'v' && !final) ? 11 : final;
		final = (c == 92 && !final) ? 92 : final;
		final = (c == sub && !final) ? sub : final;
		final = (c == '?' && !final) ? '?' : final;
		final = (c == '$' && !final) ? '$' : final;
		final2 = (final) ? 0 : c;
	}
	return (final2 ? 2 : 1);
}

static int	please_normed(int *pos, int *ipos, t_env *env)
{
	char	*tmp;

	tmp = NULL;
	if (!(tmp = find_content(env, "HOME")))
		return (1);
	*pos += ft_strlen(tmp);
	*ipos += 1;
	ft_strdel(&tmp);
	return (0);
}

static int	please_normedv2(int *ipos, char *line, t_env *env)
{
	char	*tmp;
	char	*tmp2;
	int		pos;

	pos = 0;
	tmp = NULL;
	tmp2 = NULL;
	*ipos += 1;
	tmp = ft_varname(&line[*ipos]);
	*ipos += ft_strlen(tmp);
	if ((tmp2 = find_content(env, tmp)))
	{
		pos += ft_strlen(tmp2);
		ft_strdel(&tmp2);
	}
	ft_strdel(&tmp);
	return (pos);
}

static void	normalizedcode(t_line *info, t_env *env, char *line)
{
	if (line[info->pos] == '$')
		info->lenmal += please_normedv2(&info->pos, line, env);
	else if ((line[info->pos] == 34 || line[info->pos] == 39)
			&& (info->sub == 0 || info->sub == line[info->pos]))
	{
		info->sub = (info->sub) ? 0 : line[info->pos];
		info->pos += 1;
	}
	else if (++info->pos)
		info->lenmal += 1;
}

t_line		ft_argsize(char *line, t_env *env)
{
	t_line	info;

	ft_uselessinit(&info.lenmal, &info.pos, &info.sub);
	if (line[0] == '~')
		if (please_normed(&info.lenmal, &info.pos, env))
			return (info);
	while (line[info.pos] && ft_insub(line[info.pos], info.sub))
	{
		info.bslash = (line[info.pos] == 92) ? 1 : 0;
		if (info.bslash)
		{
			info.lenmal += spcl_len(line[info.pos + 1], info.sub);
			info.pos += 2;
		}
		else
			normalizedcode(&info, env, line);
	}
	return (info);
}
