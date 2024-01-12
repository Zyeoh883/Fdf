/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:27:09 by zyeoh             #+#    #+#             */
/*   Updated: 2024/01/12 17:06:43 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_op_to_line(t_node *node, float (*f)(t_node *node,
			float matrix[3]), float matrix[3][3])
{
	t_node	*temp;

	if (!node)
		return ;
	if (f == multiply)
	{
		temp = set_node(node->x, node->y, node->z);
		if (!temp)
			return ;
		node->x = f(temp, matrix[0]);
		node->y = f(temp, matrix[1]);
		node->z = f(temp, matrix[2]);
		free(temp);
	}
	else if (f == add)
		(void)f(node, matrix[0]);
	apply_op_to_line(node->rightnode, f, matrix);
}

float	add(t_node *node, float matrix[3])
{
	node->x += matrix[0];
	node->y += matrix[1];
	node->z += matrix[2];
	return (1);
}

float	multiply(t_node *node, float matrix[3])
{
	float	x;
	float	y;
	float	z;

	x = node->x * matrix[0];
	y = node->y * matrix[1];
	z = node->z * matrix[2];
	return (x + y + z);
}
