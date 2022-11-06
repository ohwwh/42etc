/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:59:50 by ohw               #+#    #+#             */
/*   Updated: 2022/01/10 18:44:44 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_di(t_tag tag, long nbr)
{
	int	ret;

	ret = ft_checkdigit(nbr, 10);
	if ((tag.precision > ret) | !tag.precision)
		ret = tag.precision;
	if ((nbr < 0) | (tag.plus | tag.space))
		ret ++;
	if (tag.width < ret)
		tag.width = ret;
	if (tag.zero && (tag.plus | tag.space))
		write(1, &(tag.first), 1);
	if (!tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	if (!tag.zero && nbr >= 0 && (tag.plus | tag.space))
		write(1, &(tag.first), 1);
	ft_putnbr_base_precision(nbr, 10, 0, tag.precision);
	if (tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	return (tag.width);
}

static int	print_u(t_tag tag, long nbr)
{
	int	ret;

	if (!tag.precision && !(tag.dot && !nbr))
		tag.precision ++;
	ret = ft_checkdigit(nbr, 10);
	if ((tag.precision > ret) | !tag.precision)
		ret = tag.precision;
	if (tag.width < ret)
		tag.width = ret;
	if (!tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	ft_putnbr_base_precision(nbr, 10, 0, tag.precision);
	if (tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	return (tag.width);
}

static int	print_x(t_tag tag, long nbr)
{
	int	ret;

	if (!tag.precision && !(tag.dot && !nbr))
		tag.precision ++;
	ret = ft_checkdigit(nbr, 16);
	if ((tag.precision > ret) | !tag.precision)
		ret = tag.precision;
	if (tag.shop && nbr)
		ret += 2;
	if (tag.width < ret)
		tag.width = ret;
	if (!tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	if (tag.shop && nbr)
		write(1, "0x", 2);
	ft_putnbr_base_precision(nbr, 16, 0, tag.precision);
	if (tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	return (tag.width);
}

static int	print_upper_x(t_tag tag, long nbr)
{
	int	ret;

	if (!tag.precision && !(tag.dot && !nbr))
		tag.precision ++;
	ret = ft_checkdigit(nbr, 16);
	if ((tag.precision > ret) | !tag.precision)
		ret = tag.precision;
	if (tag.shop && nbr)
		ret += 2;
	if (tag.width < ret)
		tag.width = ret;
	if (!tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	if (tag.shop && nbr)
		write(1, "0X", 2);
	ft_putnbr_base_precision(nbr, 16, 1, tag.precision);
	if (tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	return (tag.width);
}

int	nbr(va_list *app, const char **fmt, t_tag tag)
{
	int		ret;
	long	nbr;

	if (**fmt == 'd' | **fmt == 'i')
	{
		nbr = (long)(va_arg(*app, int));
		if (!tag.precision && !(tag.dot && !nbr))
			tag.precision ++;
		if (nbr < 0 && tag.zero)
		{
			nbr *= -1;
			tag.plus = 1;
			tag.first = '-';
		}
		ret = print_di(tag, nbr);
	}
	else if (**fmt == 'u')
		ret = print_u(tag, (long)(va_arg(*app, unsigned int)));
	else if (**fmt == 'x')
		ret = print_x(tag, (long)(va_arg(*app, unsigned int)));
	else
		ret = print_upper_x(tag, (long)(va_arg(*app, unsigned int)));
	(*fmt)++;
	return (ret);
}
