/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <naastrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:13:24 by naastrak          #+#    #+#             */
/*   Updated: 2026/03/08 17:13:44 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_file_valid(char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4))
	{
		ft_putstr_fd("Error\nTexture must be a .xpm file\n", 2);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nTexture file not found or unreadable\n", 2);
		return (0);
	}
	close(fd);
	return (1);
}

static int	is_valid_texture(char **tex)
{
	if (count_elem(tex) != 2)
	{
		ft_putstr_fd("Error\nInvalid texture line format\n", 2);
		return (0);
	}
	return (is_file_valid(tex[1]));
}

static int	copy_path(t_game *game, char **words)
{
	char	**target;

	target = NULL;
	if (!ft_strncmp(words[0], "NO", 3))
		target = &game->map.no_path;
	else if (!ft_strncmp(words[0], "SO", 3))
		target = &game->map.so_path;
	else if (!ft_strncmp(words[0], "WE", 3))
		target = &game->map.we_path;
	else if (!ft_strncmp(words[0], "EA", 3))
		target = &game->map.ea_path;
	if (!target)
		return (0);
	if (*target != NULL)
	{
		ft_putstr_fd("Error\nDuplicate texture\n", 2);
		return (0);
	}
	*target = ft_strdup(words[1]);
	return (*target != NULL);
}

int	parse_texture(t_game *game, char *line)
{
	char	**words;
	int		ret;

	replace_tabs(line);
	words = ft_split(line, ' ');
	if (!words)
		return (0);
	if (!words[0])
	{
		free_tab(words);
		return (1);
	}
	if (!is_valid_texture(words))
	{
		free_tab(words);
		return (0);
	}
	ret = copy_path(game, words);
	free_tab(words);
	return (ret);
}
