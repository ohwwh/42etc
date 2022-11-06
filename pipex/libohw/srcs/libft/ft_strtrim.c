/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:03:13 by ohw               #+#    #+#             */
/*   Updated: 2021/11/30 20:28:26 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set ++;
	}
	return (0);
}

static int	getbuf(char const *s1, char const *set)
{
	int		buf;
	char	*temp;

	buf = 0;
	temp = (char *)s1;
	while (ft_isset(*temp, set))
		temp ++;
	while (*temp)
	{
		temp ++;
		buf ++;
	}
	if (buf <= 0)
		return (1);
	temp --;
	while (ft_isset(*temp, set))
	{
		temp --;
		buf --;
	}
	return (buf + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		buf;
	int		i;
	char	*ret;

	if (!s1)
		return (0);
	i = 0;
	buf = getbuf(s1, set);
	while (ft_isset(*s1, set))
		s1 ++;
	ret = (char *)malloc(sizeof(char) * buf);
	if (ret)
	{
		while (i < buf - 1)
		{
			ret[i] = *s1;
			i ++;
			s1 ++;
		}
		ret[i] = 0;
	}
	return (ret);
}
