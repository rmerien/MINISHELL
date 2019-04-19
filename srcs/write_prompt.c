/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_promt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 20:22:18 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/22 11:46:30 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "minishell.h"

int		write_prompt(char tmp[PATH_MAX])
{
	long	cur_time;

	cur_time = time(NULL);
	write(1, "\x1b[32;01m", 9);
	write(1, "minishell-42""\x1b[0m ""\x1b[34;01m""[", 26);
	write(1, (ctime(&cur_time) + 11), 8);
	write(1, "]""\x1b[0m"" [", 8);
	write(1, tmp, ft_strlen(tmp));
	write(1, "]\n""\x1b[37;01m""-> ""\x1b[0m", 17);
	return (0);
}
