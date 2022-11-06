/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:22:26 by ohw               #+#    #+#             */
/*   Updated: 2022/01/06 14:38:35 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print(void *p, int fd)
{
	char			c;
	unsigned long	p2;

	p2 = (unsigned long)p;
	if (p2 == 0)
		return ;
	print((void *)(p2 / 16), fd);
	if (p2 % 16 < 10)
		c = p2 % 16 + '0';
	else
		c = p2 % 16 + 87;
	write(fd, &c, 1);
}

void	ft_putaddress_fd(void *p, int fd)
{
	write(1, "0x", 2);
	if (!p)
		write(1, "0", 1);
	else
		print(p, fd);
}
