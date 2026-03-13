/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:26:23 by naastrak          #+#    #+#             */
/*   Updated: 2025/05/04 16:26:25 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while (nptr[i] == 32 || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign = -1;
		i++;
	}
	while (48 <= nptr[i] && nptr[i] <= 57)
	{
		number = number * 10 + (nptr[i] - 48);
		i++;
	}
	return (number * sign);
}
