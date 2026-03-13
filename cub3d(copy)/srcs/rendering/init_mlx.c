/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhen <xzhen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:11:56 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/07 22:49:59 by xzhen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*初始化图形系统（MLX）:
1 初始化 MLX
2 创建窗口
3 创建图像缓冲区
/*
如果 MLX 初始化失败,打印错误并退出
*/
static void	mlx_fatal(t_game *game, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free_game(game);
	exit(1);//推出程序
}

/*
用mlx创建窗口
*/
static void	init_window(t_game *game)
{
	game->mlx_data->window = mlx_new_window(game->mlx_data->ptr_mlx,
			WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->mlx_data->window)
		mlx_fatal(game, "Window creation failed");
}

/*
**创建一张图像，然后拿到它的像素内存地址,这样程序就可以直接修改像素,这就是 put_pixel() 能工作的原因。
*/
static void	init_image(t_game *game)
{
	game->mlx_data->image = mlx_new_image(game->mlx_data->ptr_mlx,
			WIN_WIDTH, WIN_HEIGHT);//创建一张图像WIN_WIDTH * WIN_HEIGHT
	if (!game->mlx_data->image)
		mlx_fatal(game, "Image creation failed");
	game->mlx_data->image_add = mlx_get_data_addr(game->mlx_data->image,
			&game->mlx_data->bits_per_pixel,//获取 image 的像素内存地址
			&game->mlx_data->line_length,//MLX 会把三个图像信息填进去:一个像素占多少bit,一行像素占多少字节,字节序一般是0
			&game->mlx_data->endian);
	if (!game->mlx_data->image_add)//如果没有成功拿到像素地址
		mlx_fatal(game, "Image data addr failed");
}

/*
** 初始化整个 MLX 图形系统:
1 初始化 MLX
2 创建窗口
3 创建图像缓冲区
*/
void	init_mlx(t_game *game)
{
	game->mlx_data->ptr_mlx = mlx_init();//返回mlx 指针
	if (!game->mlx_data->ptr_mlx)//ptr_mlx = MLX图形系统,如果为空
		mlx_fatal(game, "MLX initialisation failed");
	init_window(game);
	init_image(game);
}
