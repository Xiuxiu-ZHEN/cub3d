/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_long.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:42:34 by naastrak          #+#    #+#             */
/*   Updated: 2025/05/04 16:54:33 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unsigned_long(unsigned long long n, int base, char *symbols)
{
	int	counter;

	counter = 0;
	if (n >= (unsigned long long)base)
		counter += ft_putnbr_unsigned_long(n / base, base, symbols);
	counter += ft_putchar(symbols[n % base]);
	return (counter);
}
