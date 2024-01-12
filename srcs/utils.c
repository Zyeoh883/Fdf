/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:04:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/01/12 17:45:28 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_rgb_value(char **str)
{
	int	result;

	if (**str != ',')
		return (0xFFFFFF);
	*str += 3;
	result = 0;
	while (ft_isalpha(**str) || ft_isdigit(**str))
	{
		result *= 16;
		if (ft_isalpha(**str))
		{
			if (**str >= 97)
				result += **str - 'a' + 10;
			else
				result += **str - 'A' + 10;
		}
		else
			result += **str - '0';
		++*str;
	}
	return (result);
}

t_node	*node_addright(t_node *map, t_node *buffer)
{
	t_node	*ptr;

	if (!map)
		return (buffer);
	ptr = map;
	while (ptr->rightnode)
		ptr = ptr->rightnode;
	ptr->rightnode = buffer;
	return (map);
}

t_node	*node_linkmap(t_node *map, t_node *line)
{
	t_node	*ptr;

	if (!map)
		return (line);
	ptr = map;
	while (ptr->downnode)
		ptr = ptr->downnode;
	while (ptr && line)
	{
		ptr->downnode = line;
		ptr = ptr->rightnode;
		line = line->rightnode;
	}
	return (map);
}

void	free_nodeline(t_node *node)
{
	t_node	*buffer;

	while (node)
	{
		buffer = node;
		node = node->rightnode;
		free(buffer);
	}
}

void	free_map(t_node *map)
{
	if (!map)
		return ;
	free_map(map->downnode);
	free_nodeline(map);
}
