#include "minirt.h"

t_vec	set_lower_left_corner(t_camera *camera)
{
	t_vec	z;
	t_vec	z_axis;
	t_vec	horizontal;
	t_vec	vertical;
	double 	t;

	z = make_vec(0,0,1);
	z_axis = make_vec(- camera->view_point.x,- camera->view_point.y, - camera->view_point.z);
	horizontal = cross(camera->view_point, z);
	t = sqrt(pow(camera->fov, 2) / dot(horizontal, horizontal));
	horizontal = v_mul_n(horizontal, t * 1200 / 800);
	camera->hor = horizontal;
	vertical = cross(horizontal, camera->view_point);
	t = sqrt(pow(camera->fov, 2) / dot(vertical, vertical));
	vertical = v_mul_n(vertical, t);
	camera->ver = vertical;
	if (z_axis.x == 0 && z_axis.y == 0)
	{
		horizontal = make_vec(1, 0, 0);
		t = sqrt(pow(camera->fov, 2) / dot(horizontal, horizontal));
		horizontal = v_mul_n(horizontal, t);
		camera->hor = horizontal;
		vertical = make_vec(0, 1, 0);
		t = sqrt(pow(camera->fov, 2) / dot(vertical, vertical));
		vertical = v_mul_n(vertical, t * 800 / 1200);
		camera->ver = vertical;
	}
	return (v_sub(camera->location, v_add(v_add(v_div_n(horizontal, 2),
					v_div_n(vertical, 2)), z_axis)));
}
