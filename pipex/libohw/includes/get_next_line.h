/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 02:07:58 by ohw               #+#    #+#             */
/*   Updated: 2022/03/14 20:54:31 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# define BUFFER_SIZE 10

size_t	gnl_strlen(char *str);
size_t	gnl_strnlen(char *str);
char	*gnl_strndup(char *src, size_t n, int flag);
char	*gnl_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
