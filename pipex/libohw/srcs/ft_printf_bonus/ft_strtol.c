/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:43:43 by ohw               #+#    #+#             */
/*   Updated: 2022/01/08 14:49:30 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pm(const char **str)
{
	int	ret;

	ret = 1;
	if (**str == '+' | **str == '-')
	{	
		if (**str == '-')
			ret = -1;
		(*str)++;
	}
	return (ret);
}

static int	ispass(long ret, int n, int i, const char *str)
{
	int	pass;

	pass = 1;
	if (i == 19)
	{
		if (ret > (LONG_MAX) / 10)
			pass = 0;
		else if (ret == (LONG_MAX) / 10)
		{
			if (n == -1 && *str - 48 >= 8)
				pass = 0;
			else if (n == 1 && *str - 48 > 7)
				pass = 0;
		}	
	}
	else if (i > 19)
		pass = 0;
	return (pass);
}

static long	longmax(long ret, int n, int i, const char *str)
{
	if (i == 19)
	{
		if (ret > (LONG_MAX) / 10)
		{
			if (n == 1)
				return (LONG_MAX);
			return ((long)LONG_MIN);
		}
		else if (ret == (LONG_MAX) / 10)
		{
			if (n == -1 && *str - 48 >= 8)
				return ((long)LONG_MIN);
			else if (n == 1 && *str - 48 > 7)
				return (LONG_MAX);
			return (0);
		}
		return (0);
	}
	else
	{
		if (n == -1)
			return ((long)LONG_MIN);
		return (LONG_MAX);
	}
}

long	ft_strtol(const char *str, const char *base)
{
	long	ret;
	int		n;
	int		i;
	int		c;

	c = checkbase(base);
	if (!c)
		return (0);
	i = 1;
	ret = 0;
	while ((9 <= *str && *str <= 13) | (*str == 32))
		str ++;
	n = pm(&str);
	while (isbase(*str, base) != -1)
	{	
		if (i >= 19 && !ispass(ret, n, i, str))
			return (longmax(ret, n, i, str));
		ret *= c;
		ret = ret + *str - 48;
		str ++;
		i ++;
	}
	return (n * ret);
}
