/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaudi <aaudi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 17:13:11 by aaudi             #+#    #+#             */
/*   Updated: 2026/11/22 07:06:10 by aaudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_specfier(char c, va_list *args)
{
	int	counter;

	counter = 0;
	if (c == 'c')
		counter = ft_putchar(va_arg(*args, int));
	else if (c == 's')
		counter = ft_putstr(va_arg(*args, char *));
	else if (c == 'p')
		counter = ft_putptr(va_arg(*args, void *));
	else if (c == 'd' || c == 'i')
		counter = ft_putnbr(va_arg(*args, int));
	else if (c == 'u')
		counter = ft_putnbr_un(va_arg(*args, unsigned int));
	else if (c == 'x' || c == 'X')
		counter = ft_putnbr_hex(c, va_arg(*args, unsigned int));
	else if (c == '%')
		counter = ft_putchar('%');
	return (counter);
}

int	ft_handle_format(const char *str, va_list *args)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			ret(&counter, ft_putchar(str[i]));
			i++;
		}
		else if (str[i + 1] == '\0')
			return (counter);
		else
		{
			ret(&counter, check_specfier(str[i + 1], args));
			i = i + 2;
		}
	}
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = ft_handle_format(format, &args);
	va_end(args);
	return (count);
}

// #include <limits.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int x = 42;

// 	ft_printf("c: %c\n", 'A');
// 	printf("c: %c\n\n", 'A');
// 	ft_printf("s: %s\n", "hello");
// 	printf("s: %s\n\n", "hello");
// 	ft_printf("p: %p\n", &x);
// 	printf("p: %p\n\n", &x);
// 	ft_printf("d: %d\n", -42);
// 	printf("d: %d\n\n", -42);
// 	ft_printf("i: %i\n", INT_MIN);
// 	printf("i: %i\n\n", INT_MIN);
// 	ft_printf("u: %u\n", UINT_MAX);
// 	printf("u: %u\n\n", UINT_MAX);
// 	ft_printf("x: %x\n", 255);
// 	printf("x: %x\n\n", 255);
// 	ft_printf("X: %X\n", 255);
// 	printf("X: %X\n\n", 255);
// 	ft_printf("%%: 100%%\n");
// 	printf("%%: 100%%\n");
// 	return (0);
// }
