/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:45:14 by naastrak          #+#    #+#             */
/*   Updated: 2025/05/04 16:45:17 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (i + 1 < size)
		{
			dst[i] = src[i];
			j++;
		}
		i++;
	}
	if (i == 0 || j < size)
		dst[j] = '\0';
	return (i);
}
