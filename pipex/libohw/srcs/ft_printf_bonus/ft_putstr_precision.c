/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 00:48:57 by ohw               #+#    #+#             */
/*   Updated: 2022/01/07 01:45:56 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_precision(char *s, int precision)
{
	if (!s)
		ft_putstr_precision("(null)", precision);
	else
	{
		while (precision -- && *s)
		{
			write(1, s, 1);
			s ++;
		}
	}
}
