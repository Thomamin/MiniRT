#include "minirt.h"

double hit_plane(t_object *ob, t_ray r)
{
	double	coefficient;
	double	constant;
	t_plane	*pl;

	pl = (t_plane *) ob->object;
	coefficient = r.dir.x * pl->normal.x + r.dir.y * pl->normal.y + r.dir.z * pl->normal.z;
	constant = pl->normal.x * (pl->center.x - r.orig.x) + pl->normal.y * (pl->center.y - r.orig.y) + pl->normal.z * (pl->center.z - r.orig.z);
	if (coefficient == 0)
		return (-1);
	return (constant / coefficient);
}

double	hit_sphere(t_object *ob, t_ray r)
{
	t_vec	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	t_sphere *s;

	s = (t_sphere *) ob->object;
	oc = v_sub(r.orig, s->center);
	a = length_squared(r.dir);
	half_b = dot(oc, r.dir);
	c = length_squared(oc) - s->radius * s->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((- half_b - sqrt(discriminant)) / a);
}

double  hit_cylinder(t_object *ob, t_ray r)
{
    t_vec   oc;
    double  a;
    double  half_b;
    double  c;
    double  discriminant;
    double  t;
	t_cylinder	*cy;

	ob->hit_part = 0;
	cy = (t_cylinder *) ob->object;
    r.dir = unit_vector(r.dir);
    oc = v_sub(r.orig, cy->center);
    a = pow(dot(r.dir, cy->normal), 2) - 1;
    half_b =  dot(oc, cy->normal) * dot(r.dir, cy->normal) - dot(oc, r.dir);
    c = cy->radius * cy->radius - dot(oc, oc) +  pow(dot(oc, cy->normal), 2);
	a *= -1;
	half_b *= -1;
	c *= -1;
    discriminant = half_b * half_b - a * c;
    t = (- half_b - sqrt(discriminant)) / a;
    if ((discriminant < 0 \
    || fabs(dot(v_sub(cy->center, at(r, t)), cy->normal)) > cy->height / 2)\
    && !hit_cylinder_cap(cy, ob, r, &t))
        return (-1.0);
    else
    {
        return (t);
    }
}

int	hit_cylinder_cap(t_cylinder *cy, t_object *ob, t_ray ray, double *t)
{
    t_vec   center[2];
    double  coefficient;
    double  constant[2];
    double  ts[2];
	
    coefficient = dot(ray.dir, cy->normal);
    if (coefficient == 0)
        return (0);
    center[0] = v_add(cy->center, v_mul_n(cy->normal, cy->height / 2));
    constant[0] = dot(cy->normal, v_sub(center[0], ray.orig));
    ts[0] = constant[0] / coefficient;
	center[1] = v_add(cy->center, v_mul_n(cy->normal, -cy->height / 2));
    constant[1] = dot(cy->normal, v_sub(center[1], ray.orig));
    ts[1] = constant[1] / coefficient;
	if (length(v_sub(ray.orig, at(ray, ts[0]))) < length(v_sub(ray.orig, at(ray, ts[1]))))
	{
    	if (cy->radius >= length(v_sub(center[0], at(ray, ts[0]))))
		{
			ob->hit_part = 1;
    	    return (*t = constant[0] / coefficient);
		}
	}
	else
	{
    	if (cy->radius >= length(v_sub(center[1], at(ray, ts[1]))))
		{
			ob->hit_part = 2;
    	    return (*t = constant[1] / coefficient);
		}
	}
	return (0);
}