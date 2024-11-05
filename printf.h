/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morip <morip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:42:52 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/05 02:05:15 by morip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);

typedef struct s_list
{
	char	c_val;
	char	*s_val;
	void	*p_val;
	int		i_val;
	int		d_val;
	unsigned int	u_val;
		
	
}	t_list;


#endif