/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:40:34 by hoh               #+#    #+#             */
/*   Updated: 2021/11/30 20:27:52 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret)
	{
		if (start >= ft_strlen(s))
		{
			ret[0] = 0;
			return (ret);
		}
		while (i < len && s[start])
		{
			ret[i] = s[start];
			i ++;
			start ++;
		}
		ret[i] = 0;
	}
	return (ret);
}
