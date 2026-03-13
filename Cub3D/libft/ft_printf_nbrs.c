/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbrs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <naastrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:40:52 by naastrak          #+#    #+#             */
/*   Updated: 2025/05/04 16:59:35 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ptr(unsigned long long ptr)
{
	int	counter;

	counter = 0;
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	counter += write(1, "0x", 2);
	counter += ft_putnbr_unsigned_long(ptr, 16, "0123456789abcdef");
	return (counter);
}

int	ft_putnbr_signed(int n)
{
	int	counter;

	counter = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		counter += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		counter += ft_putnbr_signed(n / 10);
	counter += ft_putchar((n % 10) + '0');
	return (counter);
}

int	ft_put_un(unsigned int n, int base, char *symbols)
{
	int	counter;

	counter = 0;
	if (n >= (unsigned int)base)
		counter += ft_put_un(n / base, base, symbols);
	counter += ft_putchar(symbols[n % base]);
	return (counter);
}
