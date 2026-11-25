/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudi <aaudi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 19:37:48 by aaudi             #+#    #+#             */
/*   Updated: 2026/11/22 05:57:46 by aaudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(int n);
int		ft_putnbr_un(unsigned int n);
int		ft_putnbr_hex(char spc, unsigned int n);
int		ft_putnbr_hex_ptr(unsigned long n);
int		ft_putptr(void *ptr);
int		ft_handle_format(const char *str, va_list *args);
int		check_specfier(char c, va_list *args);
int		ft_printf(const char *s, ...);
void	ret(int *counter, int r);

#endif