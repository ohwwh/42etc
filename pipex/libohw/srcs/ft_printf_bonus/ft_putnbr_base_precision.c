/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_precision.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:47:22 by ohw               #+#    #+#             */
/*   Updated: 2022/01/06 14:48:40 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print(long n, int base, int capital, int precision)
{
	char	c;

	if (!n && precision <= 0)
		return ;
	print(n / base, base, capital, precision - 1);
	if (n % base < 10)
		c = n % base + '0';
	else if (n % base >= 10 && !capital)
		c = n % base + 87;
	else
		c = n % base + 55;
	write(1, &c, 1);
}

void	ft_putnbr_base_precision(long n, int base, int capital, int precision)
{
	if (n < 0)
	{
		write(1, "-", 1);
		print(-n, base, capital, precision);
	}
	else
		print(n, base, capital, precision);
}
