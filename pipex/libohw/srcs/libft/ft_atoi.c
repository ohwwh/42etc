/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:43:43 by ohw               #+#    #+#             */
/*   Updated: 2021/12/28 00:41:25 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static int	ispass(long long ret, int n, int i, const char *str)
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

static int	longmax(long long ret, int n, int i, const char *str)
{
	if (i == 19)
	{
		if (ret > (LONG_MAX) / 10)
		{
			if (n == 1)
				return ((int)LONG_MAX);
			return ((int)LONG_MIN);
		}
		else if (ret == (LONG_MAX) / 10)
		{
			if (n == -1 && *str - 48 >= 8)
				return ((int)LONG_MIN);
			else if (n == 1 && *str - 48 > 7)
				return ((int)LONG_MAX);
			return (0);
		}
		return (0);
	}
	else
	{
		if (n == -1)
			return ((int)LONG_MIN);
		return ((int)LONG_MAX);
	}
}

int	ft_atoi(const char *str)
{
	long long	ret;
	int			n;
	int			i;

	i = 1;
	ret = 0;
	while ((9 <= *str && *str <= 13) | (*str == 32))
		str ++;
	n = pm(&str);
	while (48 <= *str && *str <= 57)
	{	
		if (i >= 19 && !ispass(ret, n, i, str))
			return (longmax(ret, n, i, str));
		ret *= 10;
		ret = ret + *str - 48;
		str ++;
		i ++;
	}
	return ((int)(n * ret));
}
