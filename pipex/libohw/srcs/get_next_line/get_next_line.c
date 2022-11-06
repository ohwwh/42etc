/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:43:31 by ohw               #+#    #+#             */
/*   Updated: 2022/03/14 20:56:13 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*chunk;
	char			temp[BUFFER_SIZE + 1];
	char			*ret;
	int				i;

	if (BUFFER_SIZE <= 0)
		return (0);
	ret = gnl_strndup(chunk, gnl_strlen(chunk), 1);
	ft_bzero(temp, sizeof(char) * (BUFFER_SIZE + 1));
	while (ret && !ft_strchr(ret, '\n') && read(fd, temp, BUFFER_SIZE) > 0)
	{
		ret = gnl_strjoin(ret, temp);
		ft_bzero(temp, sizeof(char) * (BUFFER_SIZE + 1));
	}
	if (ret)
	{
		i = gnl_strnlen(ret);
		chunk = gnl_strndup(&ret[i], gnl_strlen(&ret[i]), 0);
		ret = gnl_strndup(ret, i, 1);
	}
	return (ret);
}
