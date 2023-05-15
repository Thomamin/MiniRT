#include "minirt.h"

int	hit_something(t_set *set, t_ray contact)
{
	t_object	*ob;
	double		t;
	double		near_t;
	double		length;
	double		near_length;

	near_length = -1;
	ob = set->objects;
	while (ob)
	{
		t = ob->hit_f(ob, contact);
		length = length_squared(at(contact, t));
		if (near_length == -1 || \
		(t > 0 && near_length > length))
		{
			near_t = t;
			near_length = length;
		}
		else
			ob->length2 = 184467440737095516;
		ob = ob->next;
	}
	if (length == 184467440737095516)
		return (0);
	return (near_t);
}

