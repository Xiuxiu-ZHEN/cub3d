/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhen <xzhen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 10:22:34 by mayoucha          #+#    #+#             */
/*   Updated: 2026/03/07 22:17:55 by xzhen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
side 的意思是：射线撞到的是哪种线
| side | 意思    |
| 0    | 撞到竖线 |
| 1    | 撞到横线 |
DDA 在循环里是这样走的：
	side_dist_x += delta_dist_x; 控制走的距离, delta_dist_x表示跨一个 x 格子需要走多远
	map_x += step_x;  控制走的方向
	意思是说, 如果step_x = 1,射线向右走一格。如果step_x = -1,射线向左走一格. 无论怎么样都会先走一格.

*/

/*
** 计算玩家到墙的真实垂直距离,perp = perpendicular 避免fisheye effect（鱼眼效果）
*/
static float	get_perp_dist(t_dda *d)
{
	if (d->side == 0)//说明先撞到竖线
		return (d->side_dist_x - d->delta_dist_x);//return 的是 玩家到墙的距离
	else//如果先撞到横线
		return (d->side_dist_y - d->delta_dist_y);
}

/*
** 根据玩家到墙的距离，计算墙在屏幕上的高度，以及从屏幕哪里开始画到哪里结束
公式:
start = WIN_HEIGHT/2 - height/2
end   = WIN_HEIGHT/2 + height/2
0
│
│   天花板
│
300  ← start
│
│   墙
│
500  ← end
│
│   地板
│
799

为什么一定是从屏幕中心开始画墙?
在 透视投影 中 视线高度/玩家眼睛高度 = 屏幕中心,所以所有物体都会围绕屏幕中心进行投影。
*/ 
//根据玩家到墙的距离，计算墙在屏幕上的高度，以及从屏幕哪里开始画到哪里结束
static void	compute_wall_bounds(float perp_dist, float *height, int *start,
			int *end)
{
	*height = (int)(WIN_HEIGHT / perp_dist); //先算墙在屏幕上的实际高度height, 公式:墙在屏幕上的高度=屏幕总高度/到墙的距离
	*start = -(*height) / 2 + WIN_HEIGHT / 2;//算出墙这一列从屏幕的哪个 y 值start开始画
	if (*start < 0)//如果墙超出了y=0
		*start = 0;//从屏幕顶部开始画,不允许墙画到屏幕上方
	*end = (*height) / 2 + WIN_HEIGHT / 2;//再算出墙这一列画到屏幕的哪个 y 值结束
	if (*end >= WIN_HEIGHT)//如果墙超出了屏幕高度 y=WIN_HEIGHT
		*end = WIN_HEIGHT - 1;//从屏幕底部开始画,不允许墙画到屏幕下方
}
/*
为什么需要镜像翻转墙?因为游戏中会出现玩家在墙的反面看墙的情况所以需要把墙的花纹翻转过来.
同一个 wall_x,从墙的另一侧看,对应的贴图列应该是反过来的,否则纹理方向会错

射线打到墙的 具体位置不同。例如可能打到0.2,或者0.8,不同位置要取不同的贴图列。
*/
/* 计算墙贴图应该使用第几列像素*/
static int	compute_tex_x(t_dda *d, t_game *game, t_texture *tex,
			float perp_dist)
{
	float	wall_x;//射线击中墙的位置
	int		tex_x;//要使用贴图texture的第几列
	//先计算 wall_x
	if (d->side == 0)//射线撞到的是格子边界那条竖墙
		wall_x = game->player.pos.y + perp_dist * d->ray_dir_y;//命中点 = 玩家位置 + 射线方向 × 距离
	else//射线撞到的是格子边界那条横墙
		wall_x = game->player.pos.x + perp_dist * d->ray_dir_x;
	wall_x -= floor(wall_x);//floor是取整函数,只取整数部分;所以这一步是在去掉整数部分,wall_x ∈ [0 , 1),意思是射线打到墙的百分比位置
	tex_x = (int)(wall_x * tex->width);//击中边缘墙的位置*贴图宽度=使用贴图第tex_x列
	if ((d->side == 0 && d->ray_dir_x > 0)//如果撞到竖墙 且 射线向右
		|| (d->side == 1 && d->ray_dir_y < 0))//如果撞到横墙 且 射线向上
		tex_x = tex->width - tex_x - 1;//那么把贴图左右翻转,因为 原tex_x + 新tex_x = width - 1
	return (tex_x);
}
/*把贴图的一列像素画成屏幕上的一列墙/在屏幕的第 col 列画一条墙*/
static void	render_wall_column(t_game *game, t_texture *tex, int col, t_wall *w)
{//                                                    墙贴图 屏幕第几列 墙的绘制信息
	float	step;//屏幕往下画 1 像素时，贴图往下走多少
	float	tex_pos;//当前走到贴图的哪一行了
	int		y;//当前正在画屏幕的哪一行
	int		tex_y;//当前应该取贴图的哪一行
	int		color;//从贴图里读出来的颜色

	step = (float)tex->height / w->height;// 贴图高度 / 墙高度=屏幕每画1像素的墙贴图要走多少像素
	tex_pos = (w->start - WIN_HEIGHT / 2 + w->height / 2) * step;//tex_pos = 贴图当前Y坐标/贴图从哪一行开始
	if (tex_pos < 0)//防止贴图坐标负数
		tex_pos = 0;
	y = w->start;
	while (y < w->end)
	{
		tex_y = (int)tex_pos;//当前贴图y坐标
		if (tex_y >= tex->height)//防止越界
			// tex_y = tex->height - 1;		
		color = *(int *)(tex->addr + (tex_y * tex->line_len)//从贴图读取颜色
				+ (w->tex_x * (tex->bpp / 8)));
		put_pixel(col, y, color, game);//画到屏幕
		tex_pos += step;//更新贴图位置
		y++;//屏幕往下画
	}
}

/**/
void	draw_wall_slice(int col, t_dda *d, t_game *game)
{
	t_texture	*tex;//当前墙要用的贴图
	t_wall		w;//这个结构是用来存墙的绘制信息。
	float		perp_dist;//玩家到墙的距离

	perp_dist = get_perp_dist(d);//根据 DDA 结果计算玩家到墙的真实距离
	if (perp_dist <= 0)//防止除零
		perp_dist = 0.1f;//设一个最小值防止崩溃
	tex = &game->tex[get_tex_index(d)];//get_tex_index根据墙方向返回：0 → 北墙1 → 南墙2 → 东墙3 → 西墙 然后取对应贴图
	//比如game->tex[0] → 北墙贴图
	compute_wall_bounds(perp_dist, &w.height, &w.start, &w.end);//根据玩家到墙的距离，计算墙在屏幕上的高度，以及从屏幕哪里开始画到哪里结束
	draw_c_f(game, col, w.start, w.end);//画天花板和地板 0 → start画天花板start → end留给墙,end → bottom画地板
	w.tex_x = compute_tex_x(d, game, tex, perp_dist);//计算墙贴图应该使用第几列像素
	render_wall_column(game, tex, col, &w);//把贴图的一列像素画成屏幕上的一列墙
}
