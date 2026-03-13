/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_m.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naastrak <naastrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:12:19 by naastrak          #+#    #+#             */
/*   Updated: 2026/03/08 17:21:26 by naastrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_width(t_list *lst)
{
	int	max;
	int	current_len;

	max = 0;
	while (lst)
	{
		current_len = ft_strlen(lst->content);
		if (current_len > max)
			max = current_len;
		lst = lst->next;
	}
	return (max);
}

int	convert_list_to_grid(t_game *game, t_list *lst)
{
	int		i;
	t_list	*tmp;

	if (!game || !lst)
		return (0);
	game->map.height = ft_lstsize(lst);
	game->map.width = get_max_width(lst);
	if (game->map.height == 0 || !alloc_map_arrays(game))
		return (0);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		game->map.grid[i] = normalise_line((char *)tmp->content,
				game->map.width);
		if (!game->map.grid[i])
			return (0);
		game->map.line_len[i] = game->map.width;
		i++;
		tmp = tmp->next;
	}
	return (1);
}

static int	read_map_loop(int fd, t_list **lst_map)
{
	char	*line;
	t_list	*node;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		remove_newline(line);
		node = ft_lstnew(line);
		if (!node)
			return (free(line), ft_lstclear(lst_map, free), 0);
		ft_lstadd_back(lst_map, node);
	}
	return (1);
}

int	parse_map(t_game *game, int fd, char *first_line)
{
	t_list	*lst_map;

	if (!first_line)
		return (0);
	remove_newline(first_line);
	lst_map = ft_lstnew(ft_strdup(first_line));
	if (!lst_map)
		return (0);
	if (!read_map_loop(fd, &lst_map))
		return (0);
	if (!convert_list_to_grid(game, lst_map))
	{
		ft_lstclear(&lst_map, free);
		return (0);
	}
	ft_lstclear(&lst_map, free);
	return (1);
}
