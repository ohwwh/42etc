/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:22:26 by ohw               #+#    #+#             */
/*   Updated: 2022/01/06 14:37:22 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print(long n, int base, int capital, int fd)
{
	char	c;

	if (n == 0)
		return ;
	print(n / base, base, capital, fd);
	if (n % base < 10)
		c = n % base + '0';
	else if (n % base >= 10 && !capital)
		c = n % base + 87;
	else
		c = n % base + 55;
	write(fd, &c, 1);
}

void	ft_putnbr_base_fd(long n, int base, int capital, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
	{
		write(fd, "-", 1);
		print(-n, base, capital, fd);
	}
	else
		print(n, base, capital, fd);
}
