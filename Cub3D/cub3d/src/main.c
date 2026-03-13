/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <naastrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:02:57 by naastrak          #+#    #+#             */
/*   Updated: 2026/03/08 17:04:29 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_args(int ac, char **av)
{
	int	len;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (0);
	}
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(av[1] + len - 4, ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid file extension (.cub required)\n", 2);
		return (0);
	}
	return (1);
}

static int	start_engine(t_game *game)
{
	game->mlx_data->window = mlx_new_window(game->mlx_data->ptr_mlx,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->mlx_data->window)
		return (0);
	game->mlx_data->image = mlx_new_image(game->mlx_data->ptr_mlx,
			WIN_WIDTH, WIN_HEIGHT);
	if (!game->mlx_data->image)
		return (0);
	game->mlx_data->image_add = mlx_get_data_addr(game->mlx_data->image,
			&game->mlx_data->bits_per_pixel, &game->mlx_data->line_length,
			&game->mlx_data->endian);
	if (!load_all_textures(game))
		return (0);
	init_hooks(game);
	return (1);
}

void	init_player_vectors(t_game *game)
{
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
	game->player.plane_x = -0.66 * game->player.dir_y;
	game->player.plane_y = 0.66 * game->player.dir_x;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!check_args(ac, av))
		return (1);
	init_game_struct(&game);
	game.mlx_data = init_mlx_data();
	if (!game.mlx_data)
	{
		ft_putstr_fd("Error\nMLX initialisation failed\n", 2);
		return (1);
	}
	if (!parse_file(av[1], &game))
	{
		free_game(&game);
		return (1);
	}
	init_player_vectors(&game);
	if (!start_engine(&game))
	{
		free_game(&game);
		return (1);
	}
	mlx_loop(game.mlx_data->ptr_mlx);
	return (0);
}
