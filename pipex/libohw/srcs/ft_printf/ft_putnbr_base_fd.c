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

void	ft_putnbr_base_fd(long n, int base, int capital, int fd)
{
	char	*buf;

	buf = ft_itoa_base(n, base, capital);
	ft_putstr_fd(buf, fd);
	free(buf);
	buf = 0;
}
