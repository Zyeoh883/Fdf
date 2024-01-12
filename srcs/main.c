/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:49:38 by zyeoh             #+#    #+#             */
/*   Updated: 2024/01/12 20:35:05 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_node	*map;

	if (ac != 2)
		return (-1);
	data.mlx_ptr = mlx_init();
	map = initialize(data.mlx_ptr, &data, av[1]);
	if (!data.mlx_ptr || !map)
		return (-1);
	
	mlx_hook(data.win_ptr, 2, 1L << 0, deal_key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, deal_key_release, &data);
	mlx_loop_hook(data.mlx_ptr, deal_rotate, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
