/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:36:11 by ohw               #+#    #+#             */
/*   Updated: 2021/11/30 20:17:19 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			cnt ++;
			while (*s && *s != c)
				s ++;
		}
		else
			s ++;
	}
	return (cnt);
}

static int	wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i ++;
	return (i);
}

static char	*ft_dup(const char *src, char c)
{
	int		i;
	char	*ret;

	ret = (char *)malloc((wordlen(src, c) + 1) * sizeof(char));
	if (ret)
	{
		i = 0;
		while (src[i] && src[i] != c)
		{
			ret[i] = src[i];
			i ++;
		}
		ret[i] = 0;
	}
	return (ret);
}

static char	**ft_clear(char **ret, int index)
{
	int		i;

	i = 0;
	while (i < index)
	{	
		free(ret[i]);
		i ++;
	}
	free(ret);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		i;

	if (!s)
		return (0);
	i = 0;
	ret = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (ret)
	{	
		while (*s)
		{
			if (*s != c && *s)
			{
				ret[i] = ft_dup(s, c);
				if (!ret[i])
					return (ft_clear(ret, i));
				i ++;
				s += wordlen(s, c);
			}
			else
				s ++;
		}
		ret[i] = 0;
	}
	return (ret);
}
