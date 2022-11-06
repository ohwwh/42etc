/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 14:49:43 by ohw               #+#    #+#             */
/*   Updated: 2022/01/08 14:49:47 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	checkbase(const char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '-' | base[i] == '+' | base[i] == ' ')
			return (0);
		j = 0;
		while (j < i)
		{
			if (base[i] == base[j])
				return (0);
			j ++;
		}
		i ++;
	}
	if (i == 1)
		i = 0;
	return (i);
}

int	isbase(char c, const char *base)
{
	int	ret;
	int	i;

	i = 0;
	ret = -1;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i ++;
	}
	return (ret);
}
