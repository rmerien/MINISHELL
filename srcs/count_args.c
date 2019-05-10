/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:53:28 by rmerien           #+#    #+#             */
/*   Updated: 2019/05/02 10:44:45 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	ft_norminet(char *line, t_line *info)
{
	char	*tmp;

	tmp = NULL;
	if (line[info->pos] == '$')
	{
		info->pos += 1;
		tmp = ft_varname(&line[info->pos]);
		info->pos += ft_strlen(tmp);
		ft_strdel(&tmp);
	}
	else if ((line[info->pos] == 34 || line[info->pos] == 39)
			&& (info->sub == 0 || info->sub == line[info->pos]))
	{
		info->sub = info->sub ? 0 : line[info->pos];
		info->pos += 1;
	}
	else
		info->pos += 1;
}

static inline void	ft_normeinit(int *a, char *b, int *c, char *line)
{
	*a = 0;
	*b = 0;
	*c = 0;
	while (line[*a] == 9 || line[*a] == 32)
		*a += 1;
}

static inline void	ft_normeisfun(char *a, int *b, char c, char d)
{
	*a = (c == '\\') ? 1 : 0;
	*b += (*a && !d) ? 1 : 0;
}

#include <stdio.h>
int					ft_argcount(char *line)
{
	t_line	info;
	int		count;

	ft_normeinit(&info.pos, &info.sub, &count, line);
	while (line[info.pos + 1])
	{
		while (line[info.pos] == 9 || line[info.pos] == 32)
			info.pos += 1;
		while (line[info.pos + 1] && ft_insub(line[info.pos], info.sub))
		{
			ft_normeisfun(&info.bslash, &info.pos, line[info.pos], info.sub);
			if (info.bslash)
			{
				if (!line[info.pos + 1])
					return (-1);
				info.pos += 2;
			}
			else
				ft_norminet(line, &info);
		}
		while (line[info.pos] == 9 || line[info.pos] == 32)
			info.pos += 1;
		count += 1;
	}
	return (info.sub ? -1 : count);
}
