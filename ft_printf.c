/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:46:04 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/14 22:04:48 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		i += write(1, "(null)", 6);
		return (i);
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchr(char c)
{
	int	i;

	write(1, &c, 1);
	i = 1;
	return (i);
}

int	ft_putnbr(int num)
{
	char	c;
	int		length;

	length = 0;
	if (num < 0)
	{
		if (num == -2147483648)
		{
			length += write(1, "-2147483648", 11);
			return (length);
		}
		length += write(1, "-", 1);
		num = -num;
	}
	if (num >= 10)
	{
		length += ft_putnbr(num / 10);
	}
	c = num % 10 + '0';
	length += write(1, &c, 1);
	return (length);
}

int	ft_putnbr_unsignedint(unsigned int num)
{
	char	c;
	int		length;

	length = 0;
	if (num >= 10)
	{
		length += ft_putnbr(num / 10);
	}
	c = num % 10 + '0';
	length += write(1, &c, 1);
	return (length);
}

static int	ft_puthex_lower(unsigned int num)
{
	const char	lower_base[16] = "0123456789abcdef";
	int			hex;
	int			length;

	hex = 0;
	length = 0;
	if (num >= 16)
	{
		length += ft_puthex_lower(num / 16);
	}
	if (num < 0)
	{
		hex = num % 16;
		length += write(1, &lower_base[16 - hex - 1], 1);
	}
	else
	{
		hex = num % 16;
		length += write(1, &lower_base[hex], 1);
	}
	return (length);
}

static int	ft_puthex_upper(unsigned int num)
{
	const char	upper_base[16] = "0123456789ABCDEF";
	int			hex;
	int			length;

	hex = 0;
	length = 0;
	if (num >= 16)
	{
		length += ft_puthex_upper(num / 16);
	}
	if (num < 0)
	{
		hex = num % 16;
		length += write(1, &upper_base[16 - hex - 1], 1);
	}
	else
	{
		hex = num % 16;
		length += write(1, &upper_base[hex], 1);
	}
	return (length);
}

static int	ft_putaddress(unsigned long int address)
{
	const char	hex_base[16] = "0123456789abcdef";
	long int	c_hex;
	int			length;

	length = 0;
	if (address == 0)
	{
		length += ft_putstr("(nil)");
		return (length);
	}
	if (address > 15)
		length += ft_putaddress(address / 16);	
	c_hex = address % 16;
	if (length == 0)
		length += write(1, "0x", 2);
	length += write(1, &hex_base[c_hex], 1);
	return (length);
}

static int	ft_check_specifier(va_list list, const char c)
{
	int		result;
	void	*ptr;

	ptr = NULL;
	result = 0;
	if (c == 'c')
		result = ft_putchr(va_arg(list, int));
	else if (c == 's')
		result = ft_putstr(va_arg(list, char *));
	else if (c == 'p')
		result = ft_putaddress((unsigned long)va_arg(list, void *));
	else if (c == 'd' || c == 'i')
		result = ft_putnbr(va_arg(list, int));
	else if (c == 'u')
		result = ft_putnbr_unsignedint(va_arg(list, unsigned int));
	else if (c == 'x')
		result = ft_puthex_lower(va_arg(list, int));
	else if (c == 'X')
		result = ft_puthex_upper(va_arg(list, int));
	else
		result = ft_putchr(c);
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	va_list	copy_list;
	size_t	i;
	int		length;

	va_start(list, format);
	va_copy(copy_list, list);
	i = 0;
	length = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			length += ft_check_specifier(copy_list, format[i]);
		}
		else
			length += ft_putchr(format[i]);
		i++;
	}
	va_end(list);
	return (length);
}

// #include <stdio.h>

// int	main(void)
// {
// 	// // char
// 	// printf("char : OK!\n");
// 	// printf("c : c = %c\n", 'K');
// 	// ft_printf("my: c = %c\n", 'K');
// 	// printf("\n");
	
// 	// string
// 	printf("c : s = %s\n", "TEST");
// 	ft_printf("my: s = %s\n", "TEST");
// 	printf(" NULL %s NULL \n", (char *)NULL);
// 	ft_printf(" NULL %s NULL \n", NULL);

// 	printf("\n");
	
// 	// pointer
// 	// void *ptr = NULL;
// 	// printf("c : *p = %p, %p\n", LONG_MIN, LONG_MAX);
// 	ft_printf("my: *p = %p\n", NULL);
// 	ft_printf("my: *p = %p, %p\n", LONG_MIN, LONG_MAX);
// 	ft_printf("my: *p = %p, %p\n", ULONG_MAX, -ULONG_MAX);

// 	printf("\n");
	
// 	// // decimal
// 	// printf("decimal : OK!\n");
// 	// printf("c : d = %d\n", 123456);
// 	// ft_printf("my: d = %d\n", 123456);
// 	// printf("\n");
	
// 	// // integer
// 	// printf("int : OK!\n");
// 	// printf("c : i = %i\n", 0);
// 	// ft_printf("my: i = %i\n", 0);
// 	// printf("\n");
	
// 	// // unsigned int
// 	// printf("unsigned int : OK!\n");
// 	// printf("c : u = %u\n", -456);
// 	// ft_printf("my: u = %u\n", -456);
// 	// printf("\n");
	
// 	// small x
// 	printf("c : x = %x\n", 0x12);
// 	ft_printf("my: x = %x\n", 0x12);
// 	printf("\n");
	
// 	// big X
// 	printf("c : X = %X\n", 0x12);
// 	ft_printf("my: X = %X\n", 0x12);
// 	printf("\n");
	
// 	// print %
// 	// printf("%% : OK!\n");
// 	// printf("c : %%\n");
// 	// ft_printf("my: %%\n");
// 	// printf("\n");

// 	// word count
// 	// printf("c : word count = %i\n", printf("c : %c, %s, %p, %d, %i, %u, %x, %X, %%\n", 'c', "String", ptr, 123456789, -987654321, 2147483647, 54321, 54321));
// 	// ft_printf("my: word count = %i\n", ft_printf("c : %c, %s, %p, %d, %i, %u, %x, %X, %%\n", 'c', "String", ptr, 123456789, -987654321, 2147483647, 54321, 54321));
// 	// printf("\n");
// 	// printf("c : %c, %s, %p, %d, %i, %u, %x, %X, %%\n",
// 	// 	'c', "String", p, 123456789, -987654321, 2147483647, 54321, 54321);
// 	// ft_printf("my: %c, %s, %p, %d, %i, %u, %x, %X, %%\n",
// 	// 	'c', "String", p, 123456789, -987654321, 2147483647, 54321, 54321);

// 	// printf("words: %d\n", a);

// 	// printf("%d\n", printf(NULL));
// 	// ptr = va_arg(list, void*);
// 	// printf("\n\ndebug: %p\n", ptr);
// }