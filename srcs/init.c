/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:57:46 by zyeoh             #+#    #+#             */
/*   Updated: 2024/01/12 23:14:27 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node	*initialize(void *mlx_ptr, t_data *img, char *av)
{
	t_node	*map;
	float	scale_factor;

	map = get_map(av);
	if (!mlx_ptr || !map)
		return (NULL);
	img->win_height = 1080;
	img->win_width = 1920;
	img->y_origin = img->win_height / 2;
	img->x_origin = img->win_width / 2;
	img->img = mlx_new_image(mlx_ptr, img->win_width, img->win_height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->map = map;
	scale_factor = 20;
	img->focal_len = 5000;
	//img->focal_len = 3500;
	scale(map, scale_factor, scale_factor, scale_factor);
	center_to_origin(map);
	display_map(img, map);
	img->win_ptr = mlx_new_window(img->mlx_ptr, img->win_width, img->win_height,
			"FdF");
	mlx_put_image_to_window(&img, img->win_ptr, img->img, 0, 0);
	img->key = -1;
	return (map);
}

t_node	*get_map(char *av)
{
	t_node	*map;
	t_node	*line;
	float	y;
	int		fd;
	char	*str;

	map = NULL;
	y = 0;
	fd = open(av, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		line = get_nodeline(str, y++);
		if (!line)
		{
			free_map(map);
			return (NULL);
		}
		map = node_linkmap(map, line);
		str = get_next_line(fd);
	}
	return (map);
}

t_node	*get_nodeline(char *str, float y)
{
	t_node	*result;
	t_node	*node;
	float	x;

	result = NULL;
	x = 0;
	while (*str)
	{
		while (*str == ' ' || *str == '\n')
			str++;
		node = set_node(x++, y, ft_atoi(str));
		if (!node)
		{
			free_nodeline(result);
			return (NULL);
		}
		while (ft_isdigit(*str) || *str == '-')
			str++;
		node->rgb = get_rgb_value(&str);
		while (*str == ' ' || *str == '\n')
			str++;
		result = node_addright(result, node);
	}
	return (result);
}

t_node	*set_node(float x, float y, float z)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->x = x;
	node->y = y;
	node->z = z;
	node->downnode = NULL;
	node->rightnode = NULL;
	return (node);
}
