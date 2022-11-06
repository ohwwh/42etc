/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:52:56 by ohw               #+#    #+#             */
/*   Updated: 2021/11/30 20:27:26 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	t;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i ++;
	t = i;
	while (i + 1 < size && src[j])
	{
		dst[i] = src[j];
		i ++;
		j ++;
	}
	dst[i] = '\0';
	while (src[j] != '\0')
		j ++;
	if (t >= size)
		return (j + size);
	else
		return (t + j);
}
