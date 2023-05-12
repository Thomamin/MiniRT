#include "minirt.h"


int	ray_color(t_ray r, t_set *set)
{
	double	t;
	t_object	*ob;
	t_vec		color;
	t_vec		contact;
	double		ratio;
	double		length;

	ob = set->objects;
	while (ob)
	{
		t = ob->hit_f(ob, r);
		if (t > 0.0)
			ob->ratio_f(r, t, ob, set);
		else
		{
			if (ob->type == 0)
				ob->length = 184467440737095516;
			else if (ob->type == 1)
			{
				ob->length = 184467440737095516;
				if (t != -1)
				 	ob->ratio_f(r, t, ob, set);
			}
			else if (ob->type == 2)
			{
				color = make_vec(0, 0, 0);
				ob->length = 184467440737095516;
			}
		}
		ob = ob->next;
	}
	length = -1;
	ob = set->objects;
	while (ob)
	{
		if (length == -1)
		{
			ratio = ob->ratio;
			length = ob->length;
			color = ob->color;
		}
		else
		{
			if (length > ob->length)
			{
				ratio = ob->ratio;
				length = ob->length;
				color = ob->color;
			}
		}
		ob = ob->next;
	}
	if (length == 184467440737095516)
		return (0);
	return (set_color(color, ratio, 0.2, set->light.power));
}

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