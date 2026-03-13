/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:39:14 by naastrak          #+#    #+#             */
/*   Updated: 2025/05/04 16:39:16 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned int	sign;

	str = (unsigned char *)s;
	sign = 0;
	while (sign < n)
	{
		if (str[sign] == (unsigned char)c)
			return ((char *)&str[sign]);
		sign++;
	}
	return (0);
}
