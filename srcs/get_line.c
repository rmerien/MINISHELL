/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:13:39 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/23 15:00:47 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		get_line(char **line)
{
	char	buf[31];
	char	*tmp;
	int		ret;

	if (!*line)
		if (!(*line = ft_strnew(0)))
			return (-4);
	while ((ret = read(0, buf, 30)) > 0)
	{
		buf[ret] = 0;
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)))
		{
			ft_strdel(&tmp);
			return (-4);
		}
		ft_strdel(&tmp);
		if (ft_strchr(*line, '\n'))
			break ;
	}
	if (!ret)
		ft_strdel(line);
	return (ret);
}
