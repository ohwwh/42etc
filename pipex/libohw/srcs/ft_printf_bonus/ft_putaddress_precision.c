/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress_precision.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:39:12 by ohw               #+#    #+#             */
/*   Updated: 2022/01/08 14:47:59 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print(unsigned long n, int precision)
{
	char	c;

	if (!n && precision <= 0)
		return ;
	print(n / 16, precision - 1);
	if (n % 16 < 10)
		c = n % 16 + '0';
	else
		c = n % 16 + 87;
	write(1, &c, 1);
}

void	ft_putaddress_precision(void *p, int precision)
{
	unsigned long	n;

	n = (unsigned long)p;
	write(1, "0x", 2);
	print(n, precision);
}
