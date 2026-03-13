/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:41:19 by naastrak          #+#    #+#             */
/*   Updated: 2025/05/04 16:41:21 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_percent(char c)
{
	int	a;

	a = '%';
	c = a;
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	len;

	if (str == NULL)
		return (write(1, "(null)", 6));
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}
