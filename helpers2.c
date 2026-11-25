/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudi <aaudi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 06:12:33 by aaudi             #+#    #+#             */
/*   Updated: 2026/11/22 06:14:03 by aaudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex(char spc, unsigned int n)
{
	char	*hex_digits_low;
	char	*hex_digits_upp;
	char	c;
	int		counter;

	hex_digits_low = "0123456789abcdef";
	hex_digits_upp = "0123456789ABCDEF";
	counter = 0;
	if (n >= 16)
		ret(&counter, ft_putnbr_hex(spc, (n / 16)));
	if (spc == 'x')
		c = hex_digits_low[n % 16];
	else if (spc == 'X')
		c = hex_digits_upp[n % 16];
	ret(&counter, write(1, &c, 1));
	return (counter);
}

int	ft_putnbr_hex_ptr(unsigned long n)
{
	char	*hex_digits;
	char	c;
	int		counter;

	hex_digits = "0123456789abcdef";
	counter = 0;
	if (n >= 16)
		ret(&counter, ft_putnbr_hex_ptr((n / 16)));
	c = hex_digits[n % 16];
	ret(&counter, write(1, &c, 1));
	return (counter);
}

int	ft_putptr(void *ptr)
{
	int				counter;
	unsigned long	address;

	address = (unsigned long)ptr;
	counter = 0;
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	counter = write(1, "0x", 2);
	ret(&counter, ft_putnbr_hex_ptr(address));
	return (counter);
}
