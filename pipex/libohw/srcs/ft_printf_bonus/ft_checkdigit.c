/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 10:40:10 by ohw               #+#    #+#             */
/*   Updated: 2022/01/08 14:47:02 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check(long nbr, int bs, int digit)
{
	if (nbr == 0)
		return (digit);
	return (check(nbr / bs, bs, digit + 1));
}

int	ft_checkdigit(long nbr, int bs)
{
	if (!nbr)
		return (1);
	else if (nbr < 0)
		return (check(-nbr, bs, 0));
	else
		return (check(nbr, bs, 0));
}
