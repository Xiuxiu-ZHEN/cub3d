/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <naastrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:10:25 by naastrak          #+#    #+#             */
/*   Updated: 2026/03/08 17:21:07 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_with_spaces(char *str, int start, int end)
{
	while (start < end)
	{
		str[start] = ' ';
		start++;
	}
	str[start] = '\0';
}

char	*normalise_line(char *content, int max_width)
{
	char	*new_line;
	int		content_len;

	new_line = malloc(sizeof(char) * (max_width + 1));
	if (!new_line)
		return (NULL);
	content_len = ft_strlen(content);
	ft_memcpy(new_line, content, content_len);
	fill_with_spaces(new_line, content_len, max_width);
	return (new_line);
}

int	alloc_map_arrays(t_game *game)
{
	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		return (0);
	game->map.line_len = malloc(sizeof(int) * game->map.height);
	if (!game->map.line_len)
	{
		free(game->map.grid);
		game->map.grid = NULL;
		return (0);
	}
	return (1);
}
