/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_non_nbr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:48:23 by ohw               #+#    #+#             */
/*   Updated: 2022/01/07 20:04:19 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int print_c(char c)
{
	int	ret;

	ret = 1;
	ft_putchar_fd(c, 1);
	return (ret);
}

static int print_s(char *s)
{
	int ret;

	if (!s)
		ret = 6;
	else
		ret = ft_strlen(s);
	ft_putstr_fd(s, 1);
	return (ret);
}

static int print_p(void *p)
{
	int ret;

	ret = ft_checkdigit_address(p);
	ret += 2;
	ft_putaddress_fd(p, 1);
	return (ret);
}

int	non_nbr(va_list *app, const char **fmt)
{
	int	ret;

	if (**fmt == 'c')
		ret = print_c((char)va_arg(*app, int));
	else if (**fmt == 's')
		ret = print_s(va_arg(*app, char *));
	else
		ret = print_p(va_arg(*app, void *));
	(*fmt) ++;
	return (ret);
}
