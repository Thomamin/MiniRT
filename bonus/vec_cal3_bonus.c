/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cal3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:10:42 by dmin              #+#    #+#             */
/*   Updated: 2023/05/16 14:10:45 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	length(t_vec e)
{
	return (sqrt(length_squared(e)));
}

t_vec	unit_vector(t_vec v)
{
	return (v_div_n(v, length(v)));
}

t_vec	v_add_n(t_vec v1, double n)
{
	t_vec	result;

	result.x = v1.x + n;
	result.y = v1.y + n;
	result.z = v1.z + n;
	return (result);
}
