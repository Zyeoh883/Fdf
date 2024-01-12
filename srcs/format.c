/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:28:38 by zyeoh             #+#    #+#             */
/*   Updated: 2024/01/12 23:24:00 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_to_origin(t_node *map)
{
	int	x_offset;
	int	y_offset;

	x_offset = -(max_x(map) / 2);
	y_offset = -(max_y(map) / 2);
	translate(map, x_offset, y_offset, 0);
	rotate_xy(map, DEGREE_5 * 9);
	rotate_yz(map, DEGREE_5 * 9);
}

float	max_x(t_node *node)
{
	while (node->rightnode)
		node = node->rightnode;
	return (node->x);
}

float	max_y(t_node *node)
{
	while (node->downnode)
		node = node->downnode;
	return (node->y);
}

// t_coords	set_coords(t_node *node_a, t_node *node_b, t_data *img)
// {
// 	t_coords	line;
// 	// int			z_scale;

// 	// if (img->focal_len)
// 	// {

// 	// }
// 	line.x0 = round(node_a->x) + img->x_origin;
// 	line.x1 = round(node_b->x) + img->x_origin;
// 	line.y0 = round(node_a->y) + img->y_origin;
// 	line.y1 = round(node_b->y) + img->y_origin;
// 	line.rgb0 = node_a->rgb;
// 	line.rgb1 = node_b->rgb;
// 	return (line);
// }

t_coords	set_coords(t_node *node_a, t_node *node_b, t_data *img)
{
	t_coords line;
	float z0_scale;
	float z1_scale;

	z0_scale = 1;
	z1_scale = 1;
	if (img->focal_len > 0)
	{
		if (img->focal_len > node_a->z)
			z0_scale = (img->focal_len - node_a->z) / img->focal_len;
		if (img->focal_len > node_b->z)
			z1_scale = (img->focal_len - node_b->z) / img->focal_len;
	}
	line.x0 = (node_a->x * z0_scale) + (float)img->x_origin;
	line.x1 = (node_b->x * z1_scale) + (float)img->x_origin;
	line.y0 = (node_a->y * z0_scale) + (float)img->y_origin;
	line.y1 = (node_b->y * z1_scale) + (float)img->y_origin;
	line.rgb0 = node_a->rgb;
	line.rgb1 = node_b->rgb;
	return (line);
}
