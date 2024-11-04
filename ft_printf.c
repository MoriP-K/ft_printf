/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:46:04 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/04 20:21:42 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

#include <stdio.h>

float	ft_avg(int num, ...)
{
	va_list	list;
	float	sum;

	va_start(list, num);
	sum = 0;
	for (int i = 0; i < num; i++)
		sum = sum + va_copy(list, va_arg(list, int));
	va_end(list);
	return (sum / num);
}
void	func(char *arg1, ...)
{
	va_list	ap;

	va_start(ap, arg1);
	printf("arg2: %d\n", va_arg(ap, int));
	printf("arg3: %lf\n", va_arg(ap, double));
	va_end(ap);
}

static void	ft_output(void *arg)
{
	t_list type;
}

static int	ft_check_specifier(va_list *list, const char c)
{
	int i = 0x2A;
	int d = va_arg(list, type);
	if (c == 'c' || c == '%')
		ft_output(va_copy(list, va_arg(list, char)));
	else if (c == 's')
		ft_output(va_copy(list, va_arg(list, char *)));
	else if (c == 'p')
		ft_output(va_copy(list, va_arg(list, void *)));
	else if (c == 'd')
		ft_output(va_copy(list, va_arg(list, int)));
	else if (c == 'i')
		ft_output(va_copy(list, va_arg(list, int)));
	else if (c == 'u')
		ft_output(va_copy(list, va_arg(list, unsigned int)));
	else if (c == 'x')
		ft_output(va_copy(list, va_arg(list, int)));
	else if (c == 'X')
 		ft_output(va_copy(list, va_arg(list, int)));
	// else if (c == '%')
	// 	ft_output(va_copy(list, va_arg(list, )));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		length;
	va_list	list;
	size_t	i;

	va_start(list, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!ft_check_specifier(&list, format[i]))
				return (0);
			
		}
		i++;
	}
	// length = ft_strlen(format);
	length = 0;
	return (length);
}

#include <stdio.h>

int	main(void)
{
	printf("%f\n", ft_avg(1, 2, 3, 4, 5));
	printf("\n");

	func("aaaa", 5, 3.14);
	// ft_printf("%s, %c, %d\n", "abc", 'K', 426);
	// printf("%s, %c, %d\n", "abc", 'K', 426);
}
