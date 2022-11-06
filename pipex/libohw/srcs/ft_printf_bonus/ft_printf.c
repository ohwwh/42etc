/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:59:03 by ohw               #+#    #+#             */
/*   Updated: 2022/01/08 15:51:28 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	nbr(va_list *app, const char **fmt, t_tag tag);
extern int	non_nbr(va_list *app, const char **fmt, t_tag tag);

static int	isflag(char f)
{
	if (f == '-' | f == '#' | f == '0' | f == ' ' | f == '+' )
		return (1);
	else if (f == '.')
		return (2);
	if (f >= '0' && f <= '9')
		return (3);
	return (0);
}

static t_tag	flag_format(const char **fmt, t_tag tag)
{
	tag.first = ' ';
	if (**fmt == '-')
		tag.hype = 1;
	else if (**fmt == '#')
		tag.shop = 1;
	else if (**fmt == ' ')
		tag.space = 1;
	else if (**fmt == '+')
	{
		tag.plus = 1;
		tag.first = '+';
	}
	else if (**fmt == '0')
	{
		tag.zero = 1;
		tag.empty = '0';
	}
	(*fmt)++;
	return (tag);
}

static t_tag	precision_format(const char **fmt, t_tag tag)
{
	tag.dot = 1;
	tag.empty = ' ';
	tag.zero = 0;
	(*fmt)++;
	return (tag);
}

t_tag	format(const char **f, t_tag tag)
{
	ft_bzero(&tag, sizeof(t_tag));
	tag.empty = ' ';
	tag.first = ' ';
	while (isflag(**f))
	{
		while (**f == '-' | **f == '#' | **f == ' ' | **f == '+' | **f == '0')
			tag = flag_format(f, tag);
		if (**f >= '0' && **f <= '9')
		{
			tag.width = ft_atoi(*f);
			*f += ft_checkdigit(tag.width, 10);
		}
		while (**f == '.')
			tag = precision_format(f, tag);
		if (**f >= '0' && **f <= '9')
		{
			tag.precision = ft_atoi(*f);
			*f += ft_checkdigit(tag.precision, 10);
		}
	}
	return (tag);
}

int	ft_printf(const char *f, ...)
{
	va_list	ap;
	int		ret;
	t_tag	tag;

	va_start(ap, f);
	ret = 0;
	while (*f)
	{
		if (*f == '%')
		{
			f ++;
			tag = format(&f, tag);
			if (*f == 'c' | *f == 's' | *f == 'p')
				ret += non_nbr(&ap, &f, tag);
			else if (*f == 'd' | *f == 'i' | *f == 'u' | *f == 'x' | *f == 'X')
				ret += nbr(&ap, &f, tag);
			else if (*f == '%')
				ret += write(1, f ++, 1);
		}
		else
			ret += write(1, f ++, 1);
	}
	va_end(ap);
	return (ret);
}
