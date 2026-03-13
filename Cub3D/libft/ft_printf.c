/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:40:34 by naastrak          #+#    #+#             */
/*   Updated: 2025/05/04 16:40:36 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		counter;

	if (format == NULL)
		return (-1);
	va_start (args, format);
	counter = 0;
	while (*format != '\0')
	{
		if (*format == '%' && *(format + 1) != '\0')
			counter += ft_print_format(*(++format), args);
		else
			counter += write(1, format, 1);
		++format;
	}
	va_end(args);
	return (counter);
}
