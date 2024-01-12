/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:00:47 by zyeoh             #+#    #+#             */
/*   Updated: 2024/01/12 17:48:31 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(t_node *node, int x, int y, int z)
{
	float	matrix[3][3];

	if ((fabs(node->x) + fabs(max_x(node)) < 5) && (fabs(node->y)
			+ fabs(max_y(node)) < 5))
		return ;
	ft_bzero(matrix, sizeof(float [3][3]));
	matrix[0][0] = x;
	matrix[0][1] = y;
	matrix[0][2] = z;
	while (node)
	{
		apply_op_to_line(node, add, matrix);
		node = node->downnode;
	}
}

void	scale(t_node *node, float x, float y, float z)
{
	float	matrix[3][3];
	float	r0;

	r0 = fabs(node->x) + fabs(node->y);
	if ((1 > r0 && (x * y * z) < 1) || (r0 > 100000 && (x * y * z) > 1))
		return ;
	ft_bzero(matrix, sizeof(float [3][3]));
	matrix[0][0] = x;
	matrix[1][1] = y;
	matrix[2][2] = z;
	while (node)
	{
		apply_op_to_line(node, multiply, matrix);
		node = node->downnode;
	}
}

void	rotate_xy(t_node *node, float degree)
{
	float	matrix[3][3];
	float	cos1;
	float	sin1;

	ft_bzero(matrix, sizeof(float [3][3]));
	cos1 = cos(degree);
	sin1 = sin(degree);
	matrix[0][0] = cos1;
	matrix[0][1] = -sin1;
	matrix[1][0] = sin1;
	matrix[1][1] = cos1;
	matrix[2][2] = 1;
	while (node)
	{
		apply_op_to_line(node, multiply, matrix);
		node = node->downnode;
	}
}

void	rotate_yz(t_node *node, float degree)
{
	float	matrix[3][3];
	float	cos1;
	float	sin1;

	ft_bzero(matrix, sizeof(float [3][3]));
	cos1 = cos(degree);
	sin1 = sin(degree);
	matrix[0][0] = 1;
	matrix[1][1] = cos1;
	matrix[1][2] = -sin1;
	matrix[2][1] = sin1;
	matrix[2][2] = cos1;
	while (node)
	{
		apply_op_to_line(node, multiply, matrix);
		node = node->downnode;
	}
}

void	rotate_xz(t_node *node, float degree)
{
	float	matrix[3][3];
	float	cos1;
	float	sin1;

	ft_bzero(matrix, sizeof(float [3][3]));
	cos1 = cos(degree);
	sin1 = sin(degree);
	matrix[1][1] = 1;
	matrix[0][0] = cos1;
	matrix[0][2] = -sin1;
	matrix[2][0] = sin1;
	matrix[2][2] = cos1;
	while (node)
	{
		apply_op_to_line(node, multiply, matrix);
		node = node->downnode;
	}
}
