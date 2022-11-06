/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:58:51 by ohw               #+#    #+#             */
/*   Updated: 2021/11/30 20:04:28 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{	
	size_t	i;

	if (n == 0)
		return (0);
	i = 1;
	while (i <= n && (*s1 | *s2))
	{
		if (*s1 != *s2)
			return ((unsigned char)(*s1) - (unsigned char)(*s2));
		if (i == n && *s1 == *s2)
			return (0);
		s1 ++;
		s2 ++;
		i ++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
