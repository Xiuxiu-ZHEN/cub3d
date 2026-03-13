/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <naastrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:20:48 by naastrak          #+#    #+#             */
/*   Updated: 2026/03/08 16:52:06 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "mlx.h"

# include "libft.h"

# ifdef __APPLE__

#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124

# else

#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

# define BLOCK 64
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define PI 3.14159265358979323846
# define FOV 1.0471975511965976f

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	float		angle;
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			left_rotate;
	int			right_rotate;
}	t_player;

typedef struct s_wall
{
	int		start;
	int		end;
	int		tex_x;
	float	height;
}	t_wall;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		*line_len;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	int		f_rgb;
	int		c_rgb;
}	t_map;

typedef struct s_texture
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		line_len;
	int		endian;
	int		bpp;
}	t_texture;

typedef struct s_dda
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_dda;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_mlx_data
{
	void	*ptr_mlx;
	void	*window;
	void	*image;
	char	*image_add;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_data;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_mlx_data	*mlx_data;
	t_texture	tex[4];
	t_color		floor;
	t_color		ceiling;
}	t_game;

typedef struct s_collision
{
	float	new_x;
	float	new_y;
	float	perp_x;
	float	perp_y;
}	t_collision;

/** ~~~~~~~~~~~~~~~~~~ PARSING ~~~~~~~~~~~~~~~~~~ **/
int		parse_file(char *path, t_game *game);
void	init_game_struct(t_game *game);
//texture
int		parse_texture(t_game *game, char *line);
//couleur
int		parse_color(t_color *color, char *line);
//map
int		parse_map(t_game *game, int fd, char *first_line);
int		convert_list_to_grid(t_game *game, t_list *lst);
int		valid_map(t_game *game);
int		valid_chars(t_game *game);
int		is_valid_char(char c);
int		check_map_closed(t_game *game);
int		flood_fill_iter(char **map, int start_x, int start_y, int height);
int		run_map_checks(t_game *game);
//player
int		valid_players(t_game *game);
//help
void	fill_with_spaces(char *str, int start, int end);
char	*normalise_line(char *content, int max_width);
int		alloc_map_arrays(t_game *game);
void	remove_newline(char *line);
void	replace_tabs(char *line);
int		count_elem(char **arr);
void	free_tab(char **tab);
void	free_game(t_game *game);

/** ~~~~~~~~~~~~~~~~~~ RENDERING ~~~~~~~~~~~~~~~~~~ **/
//initialisation
void	init_mlx(t_game *game);
int		close_game(t_game *game);
int		load_texture(t_game *game, t_texture *tex, char *path);
int		load_all_textures(t_game *game);

t_mlx_data				*init_mlx_data(void);
//input
int		init_hooks(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
//player
void	move_player(t_player *player, t_game *game);
void	set_player_position(t_game *game);
void	set_angle(t_player *player, char c);
//rendering and drawing
int		draw_loop(t_game *game);
void	clear_image(t_game *game);
void	put_pixel(int x, int y, int color, t_game *game);
void	draw_line(t_player *player, t_game *game, int col);
void	draw_c_f(t_game *game, int col, int start_y, int end_y);
//raycasting
void	init_dda(t_dda *d, t_player *p, float camera_x);
void	draw_wall_slice(int col, t_dda *d, t_game *game);
int		get_tex_index(t_dda *d);
//help
int		touch(float px, float py, t_game *game);
int		rgb_to_int(t_color color);

#endif