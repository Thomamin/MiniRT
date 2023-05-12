#include "minirt.h"

int	hit_something(t_set *set, t_ray contact)
{
	t_object	*ob;
	double		t;
	double		length;
	t_vec		near;

	ob = set->objects;
	while (ob)
	{
		if (ob->type == 0)
		{
			t = hit_sphere(ob, contact);
			if (t > 0)
			{
				ob->check = t;
				near = at(contact, t);
				ob->length2 = length_squared(near);
			}
			else
				ob->length2 = 184467440737095516;
		}
		else if (ob->type == 1)
		{
			t = hit_cylinder(ob, contact);
			if (t > 0)
			{
				ob->check = t;
				near = at(contact, t);
				ob->length2 = length_squared(near);
			}
			else
				ob->length2 = 184467440737095516;
		}
		else if (ob->type == 2)
		{
			t = hit_plane(ob, contact);
			if (t > 0)
			{
				ob->check = t;
				near = at(contact, t);
				ob->length2 = length_squared(near);
			}
			else
				ob->length2 = 184467440737095516;
		}
		ob = ob->next;
	}
	length = -1;
	ob = set->objects;
	while (ob)
	{
		if (length == -1)
		{
			length = ob->length2;
			t = ob->check;
		}
		else
		{
			if (length > ob->length2)
			{
				t = ob->check;
				length = ob->length2;
			}
		}
		ob = ob->next;
	}
	if (length == 184467440737095516)
		return (0);
	return (t);
}

