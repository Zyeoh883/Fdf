/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:28:15 by zyeoh             #+#    #+#             */
/*   Updated: 2024/01/12 22:54:20 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//oclusion culling
void	plotline(t_node *node_a, t_node *node_b, t_data *img)
{
	t_coords	line;

	line = set_coords(node_a, node_b, img);
	if ((line.x0 > img->win_width && line.x1 > img->win_width) || (line.x0 < 0
			&& line.x1 < 0) || (line.y0 > img->win_height
			&& line.y1 > img->win_height) || (line.y0 < 0 && line.y1 < 0))
		return ;
	if (abs(line.y1 - line.y0) < abs(line.x1 - line.x0))
	{
		if (line.x1 - line.x0 == 0)
			return ;
		if (line.x0 > line.x1)
			line = set_coords(node_b, node_a, img);
		plotlinelow(line, img);
	}
	else
	{
		if (line.y1 - line.y0 == 0)
			return ;
		if (line.y0 > line.y1)
			line = set_coords(node_b, node_a, img);
		plotlinehigh(line, img);
	}
}

void	plotlinelow(t_coords line, t_data *img)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;

	dx = line.x1 - line.x0;
	dy = abs(line.y1 - line.y0);
	yi = 1;
	if (line.y1 < line.y0)
		yi = -1;
	d = (2 * dy) - dx;
	while (line.x0 <= line.x1)
	{
		my_mlx_put_pixels(img, line.x0, line.y0, lerp_rgb(line.rgb0, line.rgb1,
				line.x1 - line.x0, dx));
		if (d > 0)
		{
			line.y0 += yi;
			d += 2 * -dx;
		}
		d += 2 * dy;
		line.x0++;
	}
}

void	plotlinehigh(t_coords line, t_data *img)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;

	dx = abs(line.x1 - line.x0);
	dy = line.y1 - line.y0;
	xi = 1;
	if (line.x1 < line.x0)
		xi = -1;
	d = (2 * dx) - dy;
	while (line.y0 <= line.y1)
	{
		my_mlx_put_pixels(img, line.x0, line.y0, lerp_rgb(line.rgb0, line.rgb1,
				line.y1 - line.y0, dy));
		if (d > 0)
		{
			line.x0 += xi;
			d += 2 * -dy;
		}
		d += 2 * dx;
		line.y0++;
	}
}

void	display_line(t_data *img, t_node *map)
{
	if (map->rightnode)
	{
		plotline(map, map->rightnode, img);
		display_line(img, map->rightnode);
	}
	if (map->downnode)
		plotline(map, map->downnode, img);
}

void	display_map(t_data *img, t_node *map)
{
	while (map)
	{
		display_line(img, map);
		map = map->downnode;
	}
}

int	lerp_rgb(int rgb0, int rgb1, float range, float d)
{
	float	k;
	int		r;
	int		g;
	int		b;
	int		squared16;

	if (rgb0 == rgb1)
		return (rgb0);
	squared16 = 256;
	k = range / d;
	r = k * getrgb(rgb0, 'r') + (1 - k) * getrgb(rgb1, 'r');
	g = k * getrgb(rgb0, 'g') + (1 - k) * getrgb(rgb1, 'g');
	b = k * getrgb(rgb0, 'b') + (1 - k) * getrgb(rgb1, 'b');
	r = r << 16;
	g = g << 8;
	return (r + g + b);
}

int	getrgb(int rgb, char c)
{
	if (c == 'b')
		return (rgb & 0xFF);
	else if (c == 'g')
		return ((rgb >> 8) & 0xFF);
	else if (c == 'r')
		return ((rgb >> 16) & 0xFF);
	return (0);
}
