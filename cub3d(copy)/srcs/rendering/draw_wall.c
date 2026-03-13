/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhen <xzhen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:14:18 by mayoucha          #+#    #+#             */
/*   Updated: 2026/03/07 22:16:10 by xzhen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Performs DDA algorithm to find the point where the ray hits a wall.
** Updates map coordinates and checks grid for '1' (wall).
*/
static int	dda_loop(t_dda *d, t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (d->side_dist_x < d->side_dist_y)//如果先撞到竖线, 让side = 0
		{
			d->side_dist_x += d->delta_dist_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else//如果先撞到横线, 让side = 1
		{
			d->side_dist_y += d->delta_dist_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (d->map_y < 0 || d->map_y >= game->map.height
			|| d->map_x < 0 || d->map_x >= game->map.width)
			return (0);
		if (game->map.grid[d->map_y][d->map_x] == '1')
			hit = 1;
	}
	return (1);
}
/*
在屏幕第 col 列画天花板和地板
*/
void	draw_c_f(t_game *game, int col, int start_y, int end_y)
{				              //屏幕第几列 墙开始的位置  墙结束的位置
	int	y;

	y = 0;//从屏幕顶部开始画天花板
	while (y < start_y)//从 0 一直画到 start_y
	{
		put_pixel(col, y, game->map.ceiling_color, game);//在屏幕 (col, y)画出天花板颜色
		y++;
	}
	y = end_y;//画地板
	while (y < WIN_HEIGHT)//从墙结束的位置开始一直画到屏幕底部
	{
		put_pixel(col, y, game->map.floor_color, game);//画出地板颜色
		y++;
	}
}

/*
** Main raycasting entry point for a single screen column.
*/
void	draw_line(t_player *player, t_game *game, int col)
{
	t_dda	d;
	float	camera_x;

	camera_x = 2.0f * col / (float)WIN_WIDTH - 1.0f;
	init_dda(&d, player, camera_x);
	if (dda_loop(&d, game))
		draw_wall_slice(col, &d, game);
}
