#include "minirt.h"


int ray_color(t_ray r, t_set *set)
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
		if (t > 0.0 && (ob->length = length(at(r, t)) < near_length))
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
	return (set_color(near->color, near->ratio, 0.2, set->light.power));
}

// int ray_color(t_ray r, t_set *set)
// {
// 	double		t;
// 	t_object	*ob;
// 	t_object	tmp;
// 	t_vec		contact;

// 	tmp.length = 184467440737095516;
// 	ob = set->objects;
// 	while (ob)
// 	{
// 		t = ob->hit_f(ob, r);
// 		if (t > 0.0)
// 			ob->ratio_f(r, t, ob, set);
// 		else
// 			ob->length = 184467440737095516;
// 		if (tmp.length > ob->length)
// 			tmp = *ob;
// 		ob = ob->next;
// 	}
// 	if (tmp.length == 184467440737095516)
// 		return (0);
// 	return (set_color(tmp.color, tmp.ratio, 0.2, set->light.power));
// }

int	set_color(t_vec ob_color, double ratio, double light, double power)
{
	int	color_red;
	int color_green;
	int color_blue;
	int color;
	double ratio1;

	if (ratio < 0)
		ratio = 0;
	ratio1 = (ratio + light) * power;
	if (ratio1 < 1)
	{
		color_red = (int)(ob_color.x * ratio1);
		color_green = (int)(ob_color.y * ratio1);
		color_blue = (int)(ob_color.z * ratio1);
	}
	else
	{
		color_red = (int)(ob_color.x * (2 - ratio1) + 255 * (ratio1 - 1));
		color_green = (int)(ob_color.y * (2 - ratio1) + 255 * (ratio1 - 1));
		color_blue = (int)(ob_color.z * (2 - ratio1) + 255 * (ratio1 - 1));
	}
	color = (color_red * 65536 + color_green * 256 + color_blue);
	return (color);
}