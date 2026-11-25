/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudi <aaudi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 19:06:18 by aaudi             #+#    #+#             */
/*   Updated: 2026/11/22 13:07:23 by aaudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ret(int *counter, int r)
{
	if (*counter == -1)
		return ;
	if (r == -1)
	{
		*counter = -1;
		return ;
	}
	*counter = *counter + r;
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i] != '\0')
	{
		ret(&counter, write(1, &s[i], 1));
		i++;
	}
	return (counter);
}

int	ft_putnbr(int n)
{
	char	c;
	int		counter;

	counter = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		counter = write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ret(&counter, ft_putnbr(n / 10));
	n = n % 10;
	c = n + '0';
	ret(&counter, write(1, &c, 1));
	return (counter);
}

int	ft_putnbr_un(unsigned int n)
{
	char	c;
	int		counter;

	counter = 0;
	if (n > 9)
		ret(&counter, ft_putnbr_un(n / 10));
	n = n % 10;
	c = n + '0';
	ret(&counter, write(1, &c, 1));
	return (counter);
}
