/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <naastrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:07:58 by naastrak          #+#    #+#             */
/*   Updated: 2026/03/08 17:20:42 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_cell(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height || x < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		return (-1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == ' ')
		return (-1);
	return (1);
}

static void	push_neighbors(int stack[10000][2], int *sp, int x, int y)
{
	if (*sp < 9996)
	{
		stack[*sp][0] = x;
		stack[(*sp)++][1] = y - 1;
		stack[*sp][0] = x;
		stack[(*sp)++][1] = y + 1;
		stack[*sp][0] = x - 1;
		stack[(*sp)++][1] = y;
		stack[*sp][0] = x + 1;
		stack[(*sp)++][1] = y;
	}
}

int	flood_fill_iter(char **map, int start_x, int start_y, int height)
{
	int	stack[10000][2];
	int	sp;
	int	x;
	int	y;
	int	check;

	sp = 0;
	stack[sp][0] = start_x;
	stack[sp++][1] = start_y;
	while (sp > 0)
	{
		sp--;
		x = stack[sp][0];
		y = stack[sp][1];
		check = check_cell(map, x, y, height);
		if (check == -1)
			return (0);
		if (check == 0)
			continue ;
		map[y][x] = 'V';
		push_neighbors(stack, &sp, x, y);
	}
	return (1);
}
