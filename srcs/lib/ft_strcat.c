/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerien <rmerien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 11:12:49 by rmerien           #+#    #+#             */
/*   Updated: 2019/03/19 11:13:34 by rmerien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
		i++;
	ft_strcpy(&s1[i], s2);
	return (s1);
}
