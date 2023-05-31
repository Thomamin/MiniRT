#include "minirt_bonus.h"

void uv_checkers(t_checker* checkers, int r_in_w, int r_in_h, t_vec color_a, t_vec color_b)
{ //checker initiating function
	checkers->width = r_in_w;
	checkers->height = r_in_h;
	checkers->color_a = color_a;
	checkers->color_b = color_b;
//	return checkers;
}

t_vec uv_pattern_at(t_checker *checkers, t_uv at)
{
	int tmp_u;
	int tmp_v;

	tmp_u = round(at.u * checkers->width);
	tmp_v = round(at.v * checkers->height);
	if ((tmp_u + tmp_v) % 2)
		return checkers->color_a;
	else
		return checkers->color_b;
}

t_uv spherical_map(t_vec p)
{
	// p는 구의 중심에서 표면에 이르는 벡터
	// p가 가르키는 3d좌표를 bitmap 2d에서 u,v로 변환하는 함수
	double	theta;
	double	phi;
	double	radius;
	t_uv	ret;

	theta = atan2(p.x, p.z);
	radius = length(p);
	phi = acos(p.y / radius);
	ret.u = 1 - (theta / (2 * PI) + 0.5);
	ret.v = 1 - (phi / PI);
	return ret;
}

//image file을 읽어서 texture 구조체에 넣는 함수
//mlx_xpm_file_to_image

//texture 구조체에서 u, v 좌표로 해당위치 color를 추출하는 함수

//t_vec pattern_at(t_texture texture, t_vec p)
t_vec pattern_at(t_checker* checker, t_vec p)
{
	t_uv uv;
	uv = spherical_map(p);
	return (uv_pattern_at(checker, uv));
}