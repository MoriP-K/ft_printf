/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:46:04 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/05 22:27:00 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

void	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_putchr(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int num)
{
	char	c;

	if (num < 0)
	{
		if (num == -2147483648)
		{
			write(1, "-2147483648", 11);
			return ;
		}
		write(1, "-", 1);
		num = -num;
	}
	if (num >= 10)
	{
		ft_putnbr(num / 10);
	}
	c = num % 10 + '0';
	write(1, &c, 1);
}

static int	ft_output(void *arg)
{
	// t_list	type;
	int	result;

	// ft_putchr(arg);
	result = 0;
	if (arg)
	{
		ft_putstr(arg);
		return (1);
	}
	return (0);
}

static int	ft_check_specifier(va_list list, const char c)
{
	int	spec;
	char *str;
	int	result;

	result = 0;
	if (c == 'c')
	{
		spec = va_arg(list, int);
		result = ft_output((char *)&spec);
	}
	else if (c == 's')
	{
		str = va_arg(list, char*);
		ft_output(str);
	}
	// else if (c == 'p')
	// 	ft_output(va_copy(list, va_arg(list, void *)));
	else if (c == 'd')
	{
		ft_putnbr(va_arg(list, int));
		result = 1;
	}
	else if (c == 'i')
	{
		ft_putnbr(va_arg(list, int));
		result = 1;
	}
	// else if (c == 'u')
	// 	ft_output(va_copy(list, va_arg(list, unsigned int)));
	// else if (c == 'x')
	// 	ft_output(va_copy(list, va_arg(list, int)));
	// else if (c == 'X')
	// 	ft_output(va_copy(list, va_arg(list, int)));
	else if (c == '%')
	{
		spec = va_arg(list, int);
		result = ft_output((char *)&c);
	}
	else
		ft_output((char *)&c);
	return (result);
}

int	ft_printf(const char *format, ...)
{
	int		length;
	va_list	list;
	va_list	copy_list;
	size_t	i;

	va_start(list, format);
	va_copy(copy_list, list);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!ft_check_specifier(copy_list, format[i]))
				i = i + 0;
			// else
			// 	ft_putchr(format[i]);
		}
		else
			ft_putchr(format[i]);
		i++;
	}
	// length = ft_strlen(format);
	length = 0;
	return (length);
}

#include <stdio.h>

int	main(void)
{
	// ft_printf("ss\n");
	// ft_printf("%c, %s,,,%d, %i", 'K', "MORIP", 42, 123456789);
	// ft_printf("%s", "MORIP");
	printf("%s, %c, %d\n", "abc", 'K', 426);
	printf("%d\n");
}
