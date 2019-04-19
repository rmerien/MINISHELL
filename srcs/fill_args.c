/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 09:41:08 by rmerien           #+#    #+#             */
/*   Updated: 2019/04/02 16:33:46 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		special_case(char *str, char c, char sub)
{
	char	final;
	char	final2;

	final = (c == 'a' && sub) ? 7 : 0;
	final = (c == 'b' && !final && sub) ? 8 : final;
	final = (c == 'e' && !final && sub) ? 27 : final;
	final = (c == 'f' && !final && sub) ? 12 : final;
	final = (c == 'n' && !final && sub) ? 10 : final;
	final = (c == 'r' && !final && sub) ? 13 : final;
	final = (c == 't' && !final && sub) ? 9 : final;
	final = (c == 'v' && !final && sub) ? 11 : final;
	final = (c == 92 && !final && sub) ? 92 : final;
	final = (c == sub && !final && sub) ? sub : final;
	final = (c == '?' && !final && sub) ? '?' : final;
	final = (c == '$' && !final && sub) ? '$' : final;
	final2 = (!final && sub) ? c : 0;
	final = (!final && sub) ? 92 : final;
	final = (final) ? final : c;
	str[0] = final;
	if (final2)
		str[1] = final2;
	return (final2 ? 2 : 1);
}

static int		please_normed(int *pos, int *ipos, char *str, t_env *env)
{
	char	*tmp;

	tmp = NULL;
	if (!(tmp = find_content(env, "HOME")))
		return (1);
	ft_strcat(str, tmp);
	*pos += ft_strlen(tmp);
	*ipos += 1;
	ft_strdel(&tmp);
	return (0);
}

static int		please_normedv2(int *ipos, char *line, char *str, t_env *env)
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
		ft_strcat(str, tmp2);
		pos += ft_strlen(tmp2);
		ft_strdel(&tmp2);
	}
	ft_strdel(&tmp);
	return (pos);
}

static void		normalizedcode(t_line *info, t_env *env, char *line, char *tf)
{
	if (line[info->pos] == '$')
		info->pos2 += please_normedv2(&info->pos, line, tf, env);
	else if ((line[info->pos] == 34 || line[info->pos] == 39)
			&& (info->sub == 0 || info->sub == line[info->pos]))
	{
		info->sub = (info->sub) ? 0 : line[info->pos];
		info->pos += 1;
	}
	else
		tf[info->pos2++] = line[info->pos++];
}

t_line			fill_arg(char *line, t_env *env, char *to_fill)
{
	t_line	info;

	ft_uselessinit(&info.pos2, &info.pos, &info.sub);
	if (line[0] == '~')
		if (please_normed(&info.pos2, &info.pos, to_fill, env))
			return (info);
	while (line[info.pos] && ft_insub(line[info.pos], info.sub))
	{
		info.bslash = (line[info.pos] == 92) ? 1 : 0;
		if (info.bslash)
		{
			info.pos2 += special_case(&to_fill[info.pos2], line[info.pos + 1],
					info.sub);
			info.pos += 2;
		}
		else
			normalizedcode(&info, env, line, to_fill);
	}
	return (info);
}
