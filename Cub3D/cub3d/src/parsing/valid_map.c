/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <naastrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:17:23 by naastrak          #+#    #+#             */
/*   Updated: 2026/03/08 17:17:40 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_chars(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (!is_valid_char(game->map.grid[y][x]))
			{
				ft_putstr_fd("Error\nInvalid character in map\n", 2);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static char	**duplicate_map(t_game *game)
{
	int		y;
	char	**copy;

	if (!game || !(game->map.height))
		return (NULL);
	copy = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	y = 0;
	while (game->map.grid[y])
	{
		copy[y] = ft_strdup(game->map.grid[y]);
		if (!copy[y])
		{
			free_tab(copy);
			return (NULL);
		}
		y++;
	}
	return (copy);
}

int	check_map_closed(t_game *game)
{
	char	**copy;
	int		result;

	copy = duplicate_map(game);
	if (!copy)
	{
		ft_putstr_fd("Error\nMalloc failed during map validation\n", 2);
		return (0);
	}
	result = flood_fill_iter(copy, (int)game->player.pos.x,
			(int)game->player.pos.y, game->map.height);
	free_tab(copy);
	if (!result)
		ft_putstr_fd("Error\nMap is not enclosed by walls\n", 2);
	return (result);
}
