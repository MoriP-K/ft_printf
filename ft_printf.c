/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:46:04 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/10 20:09:51 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

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

void	ft_putnbr_unsignedint(unsigned int num)
{
	char	c;

	// if (num < 0)
	// {
	// 	if (num == -2147483648)
	// 	{
	// 		write(1, "-2147483648", 11);
	// 		return ;
	// 	}
	// 	write(1, "-", 1);
	// 	num = -num;
	// }
	if (num >= 10)
	{
		ft_putnbr(num / 10);
	}
	c = num % 10 + '0';
	write(1, &c, 1);
}

static int	ft_output(void *arg)
{
	int	result;

	result = 0;
	if (arg)
	{
		ft_putstr(arg);
		return (1);
	}
	return (0);
}

static void ft_puthex_lower(int num)
{
	const char	lower_base[16]= "0123456789abcdef";
	int		hex;

	hex = 0;
	if (num >= 16)
	{
		ft_puthex_lower(num / 16);
	}
	if (num < 0)
	{
		hex = num % 16;
		write(1, &lower_base[16 - hex - 1], 1);
	}
	else
	{
		hex = num % 16;
		write(1, &lower_base[hex], 1);
	}
}
static void ft_puthex_upper(int num)
{
	const char	upper_base[16]= "0123456789ABCDEF";
	int		hex;

	hex = 0;
	if (num >= 16)
	{
		ft_puthex_upper(num / 16);
	}
	if (num < 0)
	{
		hex = num % 16;
		write(1, &upper_base[16 - hex - 1], 1);
	}
	else
	{
		hex = num % 16;
		write(1, &upper_base[hex], 1);
	}
}

static void	ft_putaddress(long int address)
{
	const char	hex_base[16] = "0123456789abcdef";
	long int		c_hex;

	// printf("test: %d\n", address);
	if (address > 16)
		ft_putaddress(address / 16);	
	c_hex = address % 16;
	write(1, &hex_base[c_hex], 1);
}

static int	ft_check_specifier(va_list list, const char c)
{
	int	spec;
	char *str;
	int	result;
	int *ptr;

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
	else if (c == 'p')
	{
		ptr = va_arg(list, void*);
		// printf("p :%p\n", ptr);
		ft_putaddress((long)ptr);
	}
	else if (c == 'd' || c == 'i')
	{
		ft_putnbr(va_arg(list, int));
		result = 1;
	}
	else if (c == 'u')
		ft_putnbr_unsignedint(va_arg(list, unsigned int));
	else if (c == 'x')
	{
		ft_puthex_lower(va_arg(list, int));
	}
	else if (c == 'X')
	{
		ft_puthex_upper(va_arg(list, int));
	}
	else if (c == '%')
	{
		ft_putchr(c);
		result = 1;
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
		}
		else
			ft_putchr(format[i]);
		i++;
	}
	va_end(list);
	// length = ft_strlen(format);
	length = 0;
	return (length);
}

#include <stdio.h>

int	main(void)
{
	int a = 1;
	int *p;
	p = &a;
	printf("c : %c, %s, %p, %d, %i, %u, %x, %X, %%\n",
		'c', "String", p, 123456789, -987654321, 2147483647, 54321, 54321);
	ft_printf("my: %c, %s, %p, %d, %i, %u, %x, %X, %%\n",
		'c', "String", p, 123456789, -987654321, 2147483647, 54321, 54321);
	// char p[4] = "1234";
	// printf("c :%p, %X\n", p, 123456);
	// ft_printf("my:%p\n", p);
	// printf("c : %x, %X\n", 123456, 123456);
	// ft_printf("my: %x, %X\n", 123456, 123456);
	printf("\n");
	// printf("%d\n", printf(NULL));
}
