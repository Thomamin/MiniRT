/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_set_ratio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:08:11 by migo              #+#    #+#             */
/*   Updated: 2023/05/16 14:24:02 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	check_in_hy(t_hyper *hy, t_set *set, t_vec normal)
{
	double		check;
	t_vec		center;

	check = dot(v_sub(set->cam.loc, hy->center), normal);
	if (check < hy->height)
	{
		center = v_add(hy->center, v_mul_n(normal, check));
		if (length(v_sub(center, set->cam.loc)) < 1 - hy->height)
			return (1);
	}
	return (0);
}

int	check_in_cn(t_cone *cn, t_set *set, t_vec normal)
{
	double		check;
	t_vec		center;

	check = dot(v_sub(set->cam.loc, cn->center), normal);
	if (check < cn->height)
	{
		center = v_add(cn->center, v_mul_n(normal, check));
		if (length(v_sub(center, set->cam.loc)) < 1 - cn->height)
			return (1);
	}
	return (0);
}

int	check_in_sp(t_sphere *sphere, t_set *set, t_ray contact)
{
	if (length(v_sub(set->cam.loc, contact.orig)) < sphere->radius)
		return (1);
	return (0);
}

int	check_in_cy(t_cylinder *cy, t_set *set, t_vec normal)
{
	double		check;
	t_vec		center;

	check = dot(v_sub(set->cam.loc, cy->center), normal);
	if (check < cy->height / 2)
	{
		center = v_add(cy->center, v_mul_n(normal, check));
		if (length(v_sub(center, set->cam.loc)) < cy->radius)
			return (1);
	}
	return (0);
}

void	hit_range(t_object *ob, t_set *set, t_ray contact, double t)
{
	t_vec	check;

	if ((int)t > 0)
	{
		check = at(contact, t);
		if (set->light.loc.x > contact.orig.x)
		{
			if (contact.orig.x < check.x && check.x < set->light.loc.x)
				ob->ratio = 0;
		}
		else
		{
			if (set->light.loc.x < check.x && check.x < contact.orig.x)
				ob->ratio = 0;
		}
	}
}

void	set_obj(t_object *ob, t_set *set, t_vec normal, t_ray con)
{
	t_sphere	*sp;
	t_cylinder	*cy;
	t_plane		*pl;
	t_cone		*cn;
	t_hyper		*hy;

	if (ob->type == SPHERE)
	{
		sp = ob->object;
		ob->color = sp->color;
		if (check_in_sp(sp, set, con))
			normal = v_mul_n(normal, -1);
	}
	else if (ob->type == CYLINDER)
	{
		cy = ob->object;
		ob->color = cy->color;
		if (check_in_cy(cy, set, normal))
			normal = v_mul_n(normal, -1);
	}
	else if (ob->type == PLANE)
	{
		pl = ob->object;
		ob->color = pl->color;
	}
	else if (ob->type == CONE)
	{
		cn = ob->object;
		ob->color = cn->color;
		if (check_in_cn(cn, set, normal))
			normal = v_mul_n(normal, -1);
	}
	else if (ob->type == HYPER)
	{
		hy = ob->object;
		ob->color = hy->color;
		if (check_in_hy(hy, set, normal))
			normal = v_mul_n(normal, -1);
	}	
	ob->ratio = dot(con.dir, normal) / length(normal) * length(con.dir);
	ob->length = length_squared(v_sub(set->cam.loc, con.orig));
}
