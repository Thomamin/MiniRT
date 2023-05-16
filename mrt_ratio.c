/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ratio.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:03:25 by migo              #+#    #+#             */
/*   Updated: 2023/05/16 14:33:05 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ratio_cy(t_ray r, double t, t_object *ob, t_set *set)
{
	t_ray		contact;
	t_vec		normal;
	t_vec		center_vec;
	t_cylinder	*cy;

	cy = ob->object;
	contact.orig = at(r, t);
	contact.dir = unit_vector(v_sub(set->light.location, contact.orig));
	contact.orig = v_add(contact.orig, contact.dir);
	if (ob->hit_part == 0)
	{
		center_vec = v_add(cy->center, \
		v_mul_n(cy->normal, dot(v_sub(contact.orig, cy->center), cy->normal)));
		normal = unit_vector(v_sub(contact.orig, center_vec));
		set_obj(ob, set, normal, contact);
	}
	else if (ob->hit_part == 1)
		set_obj(ob, set, cy->normal, contact);
	else
	{
		normal = v_mul_n(cy->normal, -1);
		set_obj(ob, set, normal, contact);
	}
	hit_range(ob, set, contact, hit_something(set, contact));
}

void	ratio_sp(t_ray r, double t, t_object *ob, t_set *set)
{
	t_ray		contact;
	t_vec		normal;
	t_sphere	*sphere;

	sphere = ob->object;
	contact.orig = at(r, t);
	normal = unit_vector(v_sub(at(r, t), sphere->center));
	contact.dir = unit_vector(v_sub(set->light.location, contact.orig));
	contact.orig = v_add(contact.orig, contact.dir);
	set_obj(ob, set, normal, contact);
	t = hit_something(set, contact);
	hit_range(ob, set, contact, hit_something(set, contact));
}

void	ratio_pl(t_ray r, double t, t_object *ob, t_set *set)
{
	t_ray	contact;
	t_plane	*pl;

	pl = ob->object;
	contact.orig = at(r, t);
	contact.dir = unit_vector(v_sub(set->light.location, contact.orig));
	contact.orig = v_add(contact.orig, contact.dir);
	set_obj(ob, set, pl->normal, contact);
	hit_range(ob, set, contact, hit_something(set, contact));
}
