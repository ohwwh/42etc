/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_non_nbr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:48:23 by ohw               #+#    #+#             */
/*   Updated: 2022/01/10 18:49:21 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_c(t_tag tag, char c)
{
	int	ret;

	ret = 1;
	if (tag.width < ret)
		tag.width = ret;
	if (!tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	ft_putchar_fd(c, 1);
	if (tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	return (tag.width);
}

static int	print_s(t_tag tag, char *s)
{
	int	ret;

	if (!s)
		ret = 6;
	else
		ret = ft_strlen(s);
	if (tag.dot && (tag.precision < ret))
		ret = tag.precision;
	else
		tag.precision = ret;
	if (tag.width < tag.precision)
		tag.width = tag.precision;
	if (!tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	ft_putstr_precision(s, tag.precision);
	if (tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	return (tag.width);
}

static int	print_p(t_tag tag, void *p)
{
	int	ret;

	if (!tag.precision && !(tag.dot && !p))
		tag.precision ++;
	ret = ft_checkdigit_address(p);
	if ((tag.precision > ret) | !tag.precision)
		ret = tag.precision;
	ret += 2;
	if (tag.width < ret)
		tag.width = ret;
	if (!tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	ft_putaddress_precision(p, tag.precision);
	if (tag.hype)
	{
		while (tag.width > ret ++)
			write(1, &(tag.empty), 1);
	}
	return (tag.width);
}

int	non_nbr(va_list *app, const char **fmt, t_tag tag)
{
	int	ret;

	if (**fmt == 'c')
		ret = print_c(tag, (char)va_arg(*app, int));
	else if (**fmt == 's')
		ret = print_s(tag, va_arg(*app, char *));
	else
		ret = print_p(tag, va_arg(*app, void *));
	(*fmt)++;
	return (ret);
}
