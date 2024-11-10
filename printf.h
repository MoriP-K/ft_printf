/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:42:52 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/10 19:58:03 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);

#endif