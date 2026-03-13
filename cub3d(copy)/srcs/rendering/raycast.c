/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhen <xzhen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:27:26 by mayoucha          #+#    #+#             */
/*   Updated: 2026/03/06 23:08:45 by xzhen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*这个文件在做什么?
初始化一条射线需要的所有数据,为 DDA 算法做准备
*/
#include "cub3d.h"

/*
** Calculates the ray direction and initial map cell position.
计算射线方向
		
用向量dir表示玩家的朝向: dir = (dir_x , dir_y) 
用向量plane表示玩家视线左右偏移的方向/程度 plane = (plane_x , plane_y)
	假设玩家朝下,dir=(0,1);
	假设玩家朝上,dir=(0,-1);
	假设FOV视野是60度,那么plane=(0,0.66);
	假设FOV视野是90度,那么plane=(0,1);
        (0,-1)
          ↑
          上
(-1,0) ←     → (1,0)
  左              右
          ↓
        (0,1)
         下
为什么 y轴是向下?因为屏幕坐标是这样：(0,0) 在左上角,y轴朝下
		(0,0) --------> x
  		|
  		|
  		|
 		v
  		y


camera_x 是什么?
camera_x ∈ [-1 , 1], 它表示：屏幕上的位置
屏幕左边射线 camera_x = -1
屏幕中间射线 camera_x = 0
屏幕右边射线 camera_x = 1

plane是什么?
站在迷宫里,看到的不是一条射线而是一个空间,所以需要一个“左右范围”,plane就表示横向方向;
plane 必须和 dir 垂直! 比如玩家向右,dir = (1 , 0), plane = (0 , 1)     这里讲的只有方向是这个方向,长度不一定
plane 的长度还决定视野FOV! plane 控制的是屏幕左右的展开角度.plane 越长,视野越宽
   \         |         /
    \        |        /
     \<------|------>/
       plane P plane
	这样就形成了一个摄像机平面 (camera plane),因为摄像机本身有长度

plane 的长度不能太大!
	假设: 玩家一开始朝右,dir = (1,0), 那么因为plane和dir垂直, plane = (0,1);
		ray = dir + plane * camera_x;
		屏幕左边的射线公式 ray = dir - plane,也就是ray=(1,-1);
		屏幕左边的射线公式 ray = dir - plane,也就是ray=(1,1); 
		这个夹角大约：90°,问题是太宽画面会变形;
		所以一般让plane = (0,0.66),左边射线ray = (1,-0.66),右边射线ray = (1,0.66);这个角度大约66°,是一个非常自然仿真的视野, 是Wolfenstein 3D 使用的经典视野。

ray = dir + plane * camera_x
射线 = 前方 + 左右偏移

*/

/*1. 计算当前屏幕列的射线方向 2. 找到射线开始所在的地图格子*/
static void	init_ray_dir_and_map(t_dda *d, t_player *p, float camera_x)
{
	d->ray_dir_x = p->dir_x + p->plane_x * camera_x;//计算射线x方向
	d->ray_dir_y = p->dir_y + p->plane_y * camera_x;//计算射线y方向
	d->map_x = (int)p->pos.x;//因为pos.x是浮点数,这一步去掉了小数,为了通过玩家位置找到对应的地图格子
	d->map_y = (int)p->pos.y;//玩家位置通常是：pos = (2.7 , 3.4) 地图格子是整数：(2 , 3)
}


/*DDA算法要做的事情是：判断下一步先碰到竖线还是横线.所以我们需要知道：到下一条竖线要走多远,到下一条横线要走多远*/
//delta_dist_x: 射线跨一个格子的X轴距离需要走多远 delta是变化量Δ
//delta_dist_y:射线跨一个格子的Y轴距离需要走多远
//fabs取绝对值,因为距离不能是负数。

/*为什么是 1 / ray_dir_x?
假设：射线方向ray = (1 , 0.5)
	 意思：x 每增加 1, y 增加 0.5
所以当射线跨过一个竖线：x + 1, 需要走的x轴距离 = 1 / ray_dir_x */

/*计算射线每跨过一格地图x轴和y轴上分别需要走多远*/
static void init_delta_dist(t_dda *d)
{
	if (d->ray_dir_x == 0.0f)//说明射线完全垂直
		d->delta_dist_x = 1e30;//1 后面 30 个 0,说明离x轴无限远,因为1 / ray_dir_x 会崩溃,所以用一个一个非常大的数表示这条射线几乎不会在 x 方向跨格
	else	
		d->delta_dist_x = fabs(1.0f / d->ray_dir_x);
	if (d->ray_dir_y == 0.0f)//说明射线完全水平
		d->delta_dist_y = 1e30;//说明离y轴无限远
	else
		d->delta_dist_y = fabs(1.0f / d->ray_dir_y);
}

// | 情况    | step_x |
// | 射线向左 | -1     |
// | 射线向右 | 1      |

// | 方向 | step_y |
// | 向上 | -1     |
// | 向下 | 1      |
//玩家到第一条格子线的距离,不是跨一格，而是先碰到最近的格子边
//玩家到第一条竖格子边的距离*delta_dist_x=射线到第一条竖格子边的实际距离;Y方向同样逻辑
//假设玩家位置：pos.x = 2.3 地图格子：map_x = 2,说明玩家在点的位置
|----|-.---|----|
  1     2    3
      map_x=2
	  pos.x=2.3

/*为什么需要 side_dist?   因为通过if (side_dist_x < side_dist_y)的对比可以知道下一条竖线近还是下一条横线近   */
/*1. 确定射线在地图里往哪个方向走 (step)2. 计算射线到第一条格子线的距离 (side_dist)*/
static void	init_step_and_side_dist(t_dda *d, t_player *p)
{
	if (d->ray_dir_x < 0.0f)
	{
		d->step_x = -1;//规定了step_x = -1的意思是射线向左
		d->side_dist_x = (p->pos.x - d->map_x) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;////射线向右
		d->side_dist_x = (d->map_x + 1.0f - p->pos.x) * d->delta_dist_x;//计算射线到第一条横格子线的距离
	}
	if (d->ray_dir_y < 0.0f)
	{
		d->step_y = -1;//射线向上
		d->side_dist_y = (p->pos.y - d->map_y) * d->delta_dist_y;
	}
	else
	{
		d->step_y = 1;////射线向下
		d->side_dist_y = (d->map_y + 1.0f - p->pos.y) * d->delta_dist_y;//计算射线到第一条竖格子线的距离
	}
}

/*
** Entry point for DDA initialisation before the main hit loop.
*/
void	init_dda(t_dda *d, t_player *p, float camera_x)
{
	init_ray_dir_and_map(d, p, camera_x);
	init_delta_dist(d);
	init_step_and_side_dist(d, p);
}
