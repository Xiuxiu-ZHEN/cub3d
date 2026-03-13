/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <naastrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:41:06 by naastrak          #+#    #+#             */
/*   Updated: 2025/05/04 17:01:36 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_format(char flag, va_list args)
{
	int	c;

	c = 0;
	if (flag == 'c')
		c += ft_putchar((char)va_arg(args, int));
	else if (flag == 's')
		c += ft_putstr(va_arg(args, char *));
	else if (flag == 'd' || flag == 'i')
		c += ft_putnbr_signed(va_arg(args, int));
	else if (flag == 'u')
		c += ft_put_un(va_arg(args, unsigned int), 10, "0123456789");
	else if (flag == 'x')
		c += ft_put_un(va_arg(args, unsigned int), 16, "0123456789abcdef");
	else if (flag == 'X')
		c += ft_put_un(va_arg(args, unsigned int), 16, "0123456789ABCDEF");
	else if (flag == 'p')
		c += ft_print_ptr((unsigned long long)va_arg(args, void *));
	else if (flag == '%')
		c += ft_putchar('%');
	else
		c += write(1, &flag, 1);
	return (c);
}
