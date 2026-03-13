/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:46:41 by naastrak          #+#    #+#             */
/*   Updated: 2025/05/04 16:46:47 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	sign;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		sign = 0;
		if (big[i] == little[sign])
		{
			while (i + sign < len && big[i + sign] == little[sign])
			{
				sign++;
				if (little[sign] == '\0')
					return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (0);
}
