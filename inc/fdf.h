/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:48:17 by zyeoh             #+#    #+#             */
/*   Updated: 2024/01/12 23:33:28 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				x_origin;
	int				y_origin;
	int				win_height;
	int				win_width;
	int				key;
	int				focal_len;
	struct s_node	*map;
}					t_data;

typedef struct s_node
{
	float			x;
	float			y;
	float			z;
	int				rgb;
	struct s_node	*rightnode;
	struct s_node	*downnode;
}					t_node;

typedef struct s_coords
{
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	int				rgb0;
	int				rgb1;
}					t_coords;

# define DEGREE_1 0.017453
# define DEGREE_5 0.087266
# define Q_KEY 12
# define W_KEY 13
# define E_KEY 14
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define PLUS_KEY 24
# define MINUS_KEY 27
# define I_KEY 34
# define J_KEY 38
# define K_KEY 40
# define L_KEY 37
# define R_KEY 15
# define T_KEY 17
# define Y_KEY 16
# define F_KEY 3
# define G_KEY 5
# define H_KEY 4
# define FIVE_KEY 23
# define SIX_KEY 22
# define SEVEN_KEY 26

void				display_line(t_data *img, t_node *map);
void				display_map(t_data *img, t_node *map);

t_node				*initialize(void *mlx_ptr, t_data *img, char *av);
t_node				*get_map(char *av);
t_node				*get_nodeline(char *str, float y);
t_node				*set_node(float x, float y, float z);
t_node				*node_addright(t_node *result, t_node *buffer);
t_node				*node_linkmap(t_node *map, t_node *line);

void				center_to_origin(t_node *map);
float				max_x(t_node *node);
float				max_y(t_node *node);

void				my_mlx_put_pixels(t_data *data, int x, int y, int color);
void				plotline(t_node *node_a, t_node *node_b, t_data *img);
void				plotlinelow(t_coords line, t_data *img);
void				plotlinehigh(t_coords line, t_data *img);
t_coords			set_coords(t_node *node_a, t_node *node_b, t_data *img);

int					get_rgb_value(char **str);
void				free_nodeline(t_node *node);
void				free_map(t_node *map);

void				translate(t_node *node, int x, int y, int z);
void				scale(t_node *node, float x, float y, float z);
void				rotate_xy(t_node *node, float degree);
void				rotate_yz(t_node *node, float degree);
void				rotate_xz(t_node *node, float degree);

void				apply_op_to_line(t_node *node, float (*f)(t_node *node,
							float matrix[3]), float matrix[3][3]);
float				add(t_node *node, float matrix[3]);
float				multiply(t_node *node, float matrix[3]);

int					render_frame(t_data *data, t_node *map);
int					deal_rotate(t_data *data);
void				clear_image(t_data *data);

int					lerp_rgb(int rgb0, int rgb1, float range, float d);
int					deal_key_release(int key, t_data *data);
int					deal_key_press(int key, t_data *data);
int					getrgb(int rgb, char c);

#endif