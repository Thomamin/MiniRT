/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ray_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:29:38 by migo              #+#    #+#             */
/*   Updated: 2023/05/16 14:29:39 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ray_color(t_ray r, t_set *set)
{
	double		t;
	double		near_t;
	double		near_length;
	t_object	*ob;
	t_object	*near;

	near_length = 184467440737095516;
	ob = set->objects;
	while (ob)
	{
		t = ob->hit_f(ob, r);
		ob->length = length(v_sub(set->camera.location, at(r, t)));
		if (t > 0 && ob->length < near_length)
		{
			near = ob;
			near_t = t;
			near_length = ob->length;
		}
		ob = ob->next;
	}
	if (near_length == 184467440737095516)
		return (0);
	near->ratio_f(r, near_t, near, set);
	return (set_color(near->color, near->ratio * set->light.power, \
	set->am_light));
}

int	set_color(t_vec ob_color, double ratio, t_am_light am)
{
	int		color_red;
	int		color_green;
	int		color_blue;
	int		color;
	t_vec	ratio1;

	if (ratio < 0)
		ratio = 0;
	ratio1 = v_add_n(v_mul_n(am.color, am.am_light), ratio);
	if (ratio1.x < 1)
		color_red = (int)(ob_color.x * ratio1.x);
	else
		color_red = (int)(ob_color.x * (2 - ratio1.x) + 255 * (ratio1.x - 1));
	if (ratio1.y < 1)
		color_green = (int)(ob_color.y * ratio1.y);
	else
		color_green = (int)(ob_color.y * (2 - ratio1.y) + 255 * (ratio1.y - 1));
	if (ratio1.z < 1)
		color_blue = (int)(ob_color.z * ratio1.z);
	else
		color_blue = (int)(ob_color.z * (2 - ratio1.z) + 255 * (ratio1.z - 1));
	color = (color_red * 65536 + color_green * 256 + color_blue);
	return (color);
}
