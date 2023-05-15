#include "minirt.h"

double  ratio_cy(t_ray r, double t, t_object *ob, t_set *set)
{
    t_ray       contact;
    t_vec       normal;
    t_vec       center_vec;
    t_cylinder  *cylinder;
    double      ratio;
	t_vec		check;
	
    cylinder = ob->object;
	r.dir = unit_vector(r.dir);
	if (ob->hit_part == 0)
	{
    	contact.orig = at(r,t);
    	center_vec = v_add(cylinder->center, \
    	v_mul_n(cylinder->normal, dot(v_sub(contact.orig, cylinder->center), cylinder->normal)));
    	normal = unit_vector(v_sub(contact.orig, center_vec));
    	contact.dir = unit_vector(v_sub(set->light.location, contact.orig));
    	ratio = dot(contact.dir, normal) / length(normal) * length(contact.dir);
    	ob->color = cylinder->color;
    	ob->ratio = ratio;
    	ob->length = length_squared(v_sub(set->camera.location, contact.orig));
	}
	else if (ob->hit_part == 1)
	{
		contact.orig = at(r,t);
		contact.dir = unit_vector(v_sub(set->light.location, contact.orig));
		ratio = dot(contact.dir, cylinder->normal) / length(cylinder->normal) * length(contact.dir);
		ob->color = cylinder->color;
		ob->ratio = ratio;
		ob->length = length_squared(v_sub(set->camera.location, contact.orig));

	}
	else
	{
		contact.orig = at(r,t);
		contact.dir = unit_vector(v_sub(set->light.location, contact.orig));
		normal = v_mul_n(cylinder->normal, -1);
		ratio = dot(contact.dir, normal) / length(normal) * length(contact.dir);
		ob->color = cylinder->color;
		ob->ratio = ratio;
		ob->length = length_squared(v_sub(set->camera.location, contact.orig));
	}
	t = hit_something(set, contact);
	if (t != 0)
	{
		check = at(contact, t);
		if (set->light.location.y > contact.orig.y)
		{
			if (contact.orig.y < check.y && check.y < set->light.location.y)
				ob->ratio = 0;
		}
		else
		{
			if (set->light.location.y < check.y && check.y < contact.orig.y)
				ob->ratio = 0;
		}
	}
    return (ratio);
}

double	ratio_sp(t_ray r, double t, t_object *ob, t_set *set)
{
	t_ray	contact;
	t_vec	normal;
	t_sphere *sphere;
	double	ratio;
	t_vec	check;

	sphere = ob->object;
	contact.orig = at(r,t);
	normal = unit_vector(v_sub(at(r, t), sphere->center));
	contact.dir = unit_vector(v_sub(set->light.location, contact.orig));
	ratio = dot(contact.dir, normal) / length(normal) * length(contact.dir);
	ob->color = sphere->color;
	ob->ratio = ratio;
	ob->length = length_squared(v_sub(set->camera.location, contact.orig));
	t = hit_something(set, contact);
	if (t != 0)
	{
		check = at(contact, t);
		if (set->light.location.y > contact.orig.y)
		{
			if (contact.orig.y < check.y && check.y < set->light.location.y)
				ob->ratio = 0;
		}
		else
		{
			if (set->light.location.y < check.y && check.y < contact.orig.y)
				ob->ratio = 0;
		}
	}
	return (ratio);
}

double	ratio_pl(t_ray r, double t, t_object *ob, t_set *set)
{
	t_ray	contact;
	t_vec	normal;
	double	ratio;
	t_vec	check;
	t_plane *pl;

	pl = ob->object;
	contact.orig = at(r,t);
	contact.dir = unit_vector(v_sub(set->light.location, contact.orig));
	ratio = dot(contact.dir, pl->normal) / length(pl->normal) * length(contact.dir);
	ob->color = pl->color;
	ob->ratio = ratio;
	ob->length = length_squared(v_sub(set->camera.location, contact.orig));
	contact.orig.x += contact.dir.x;
	contact.orig.y += contact.dir.y;
	contact.orig.z += contact.dir.z;
	t = hit_something(set, contact);
	if (t > 0)
	{
		check = at(contact, t);
		if (set->light.location.x > contact.orig.x)
		{
			if (contact.orig.x < check.x && check.x < set->light.location.x)
				ob->ratio = 0;
		}
		else
		{
			if (set->light.location.x < check.x && check.x < contact.orig.x)
				ob->ratio = 0;
		}
	}
	return (ratio);
}