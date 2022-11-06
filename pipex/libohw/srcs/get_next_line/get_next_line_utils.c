/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:04:21 by ohw               #+#    #+#             */
/*   Updated: 2022/03/14 20:53:07 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

size_t	gnl_strnlen(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len] && str[len] != '\n')
		len++;
	if (str && str[len] == '\n')
		len ++;
	return (len);
}

char	*gnl_strndup(char *src, size_t n, int flag)
{
	size_t	i;
	char	*ret;

	if (src && !*src)
	{
		if (flag)
			free(src);
		return (0);
	}	
	ret = (char *)malloc((n + 1) * sizeof(char));
	if (ret)
	{
		i = 0;
		while (src && i < n)
		{
			ret[i] = src[i];
			i ++;
		}
		ret[i] = '\0';
		if (flag)
			free(src);
		return (ret);
	}
	return (0);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;

	if (!s1 && !s2)
		return (0);
	i = 0;
	ret = (char *)malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (ret)
	{
		while (s1 && s1[i])
		{
			ret[i] = s1[i];
			i ++;
		}
		while (s2 && *s2)
		{
			ret[i] = *s2;
			i ++;
			s2 ++;
		}
		ret[i] = 0;
		free(s1);
	}
	return (ret);
}
