/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:50:48 by zyeoh             #+#    #+#             */
/*   Updated: 2024/01/12 23:31:11 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_data *data)
{
	ft_bzero(data->addr, data->win_height * data->line_length);
}

void	my_mlx_put_pixels(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (0 > x || x >= data->win_width || 0 > y || y >= data->win_height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	render_frame(t_data *data, t_node *map)
{
	clear_image(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	display_map(data, map);
	mlx_put_image_to_window(&data, data->win_ptr, data->img, 0, 0);
	return (0);
}

int	deal_rotate(t_data *data)
{
	if (data->key == -1)
		return (0);
	if (data->key == W_KEY)
		rotate_yz(data->map, DEGREE_1 * 2);
	else if (data->key == A_KEY)
		rotate_xy(data->map, -DEGREE_1 * 2);
	else if (data->key == S_KEY)
		rotate_yz(data->map, -DEGREE_1 * 2);
	else if (data->key == D_KEY)
		rotate_xy(data->map, DEGREE_1 * 2);
	else if (data->key == Q_KEY)
		rotate_xz(data->map, DEGREE_1 * 2);
	else if (data->key == E_KEY)
		rotate_xz(data->map, -DEGREE_1 * 2);
	else if (data->key == PLUS_KEY)
		scale(data->map, 1.1, 1.1, 1.1);
	else if (data->key == MINUS_KEY)
		scale(data->map, 0.9, 0.9, 0.9);
	else if (data->key == I_KEY)
		translate(data->map, 0, -10, 0);
	else if (data->key == J_KEY)
		translate(data->map, -10, 0, 0);
	else if (data->key == K_KEY)
		translate(data->map, 0, 10, 0);
	else if (data->key == L_KEY)
		translate(data->map, 10, 0, 0);
	else if (data->key == R_KEY)
		scale(data->map, 1.1, 1, 1);
	else if (data->key == F_KEY)
		scale(data->map, 0.9, 1, 1);
	else if (data->key == T_KEY)
		scale(data->map, 1, 1.1, 1);
	else if (data->key == G_KEY)
		scale(data->map, 1, 0.9, 1);
	else if (data->key == Y_KEY)
		scale(data->map, 1, 1, 1.1);
	else if (data->key == H_KEY)
		scale(data->map, 1, 1, 0.9);
	else if (data->key == SEVEN_KEY)
		data->focal_len += 1000;
	else if (data->key == SIX_KEY && data->focal_len > 1000)
		data->focal_len = 0;
	else if (data->key == FIVE_KEY && data->focal_len > 0)
		data->focal_len = 0;
	else if (data->key == FIVE_KEY && data->focal_len < 10000)
		data->focal_len = 10000;
	return (render_frame(data, data->map));
}

// else if (data->key == T_KEY)
// 	scale(data->map, 1, 1.1, 1);
// else if (data->key == G_KEY)
// 	scale(data->map, 1, 0.9, 1);

int	deal_key_release(int key, t_data *data)
{
	if (data->key == key)
		data->key = -1;
	return (0);
}

int	deal_key_press(int key, t_data *data)
{
	if (key == 53)
	{
		free_map(data->map);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	data->key = key;
	return (0);
}
