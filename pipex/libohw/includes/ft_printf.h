/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:47:29 by ohw               #+#    #+#             */
/*   Updated: 2022/02/15 22:32:56 by ohw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_putnbr_base_fd(long n, int base, int capital, int fd);
void	ft_putaddress_fd(void *p, int fd);
int		ft_printf(const char *fmt, ...);
int		ft_checkdigit(long nbr, int bs);
int		ft_checkdigit_address(void	*p);

#endif
