/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:54:18 by migo              #+#    #+#             */
/*   Updated: 2023/05/12 18:22:55 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "/Users/thomamin/prj/minirt/lib/mlx/mlx.h"
# include "get_next_line.h"

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}		t_vec;

typedef struct s_light
{
	t_vec	location;
	double	power;
}		t_light;

typedef struct s_ray
{
	t_vec	orig;
	t_vec	dir;
}		t_ray;

typedef struct s_sphere
{
	t_vec	center;
	double	radius;
	t_vec	color;
}		t_sphere;

typedef struct s_am_light
{
	double	am_light;
	t_vec	color;
}		t_am_light;

typedef struct s_plane
{
	t_vec	center;
	t_vec	normal;
	t_vec	color;
}		t_plane;

typedef struct s_cylinder
{
	t_vec	center;
	t_vec	normal;
	double	height;
	double	radius;
	t_vec	top;
	t_vec	botton;
	t_vec	h;
	t_vec	color;
}		t_cylinder;

typedef struct s_camera
{
	t_vec	location;
	t_vec	view_point;
	t_vec	hor;
	t_vec	ver;
	t_vec	lower_left_corner;
	double	fov;
}		t_camera;

typedef struct s_set
{
	t_camera	camera;
	t_light		light;
	t_am_light	am_light;
	struct s_object	*objects;
}		t_set;

typedef struct s_object
{
	int				type;
	double			ratio;
	double			length;
	double			length2;
	double			hit_part;
	double			check;
	t_vec			color;
	void			*object;
	double			(*hit_f) (struct s_object*, t_ray);
	double			(*ratio_f) (t_ray, double, struct s_object*, struct s_set*);
	struct s_object	*next;
}		t_object;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int	line_length;
	int	endian;
}	t_data;

t_vec		make_vec(double x, double y, double z);
t_vec		v_mul_n(t_vec v1, float n);
t_vec		v_mul(t_vec v1, t_vec v2);
t_vec		v_sub(t_vec v1, t_vec v2);
t_vec		v_add(t_vec v1, t_vec v2);
t_vec		v_div_n(t_vec v1, float n);
t_vec		cross(t_vec v1, t_vec v2);
double		degrees_to_radians(double degrees);
double		dot(t_vec v1, t_vec v2);
double		length_squared(t_vec e);
t_vec		at(t_ray r, double t);
t_vec		unit_vector(t_vec v);
double		length(t_vec e);

t_object	*ft_lstnew(int nb, char *map);
void		ft_lstadd_front(t_object **lst, t_object *new);
void		ft_lstclear(t_object **lst);

double		ft_atof(char **map);
void		checkmap(char **argv, t_set	*set);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

int			set_color(t_vec ob_color, double ratio, double light, double power);
int			ray_color(t_ray r, t_set *set);

void		set_camera(t_camera *camera, char *map);
void		set_light(t_light *light, char *map);
t_plane		*set_plane(char *map);
t_cylinder	*set_cylinder(char *map);
t_sphere	*set_sphere(char *map);
void		set_am_light(t_am_light *am_light, char *map);

t_vec		set_lower_left_corner(t_camera *camera);

double 		hit_plane(t_object *ob, t_ray r);
double		hit_sphere(t_object *ob, t_ray r);
double  	hit_cylinder(t_object *ob, t_ray r);
int      	hit_cylinder_cap(t_cylinder *cy, t_object *ob, t_ray ray, double *t);
int			hit_something(t_set *set, t_ray contact);

double		ratio_cy(t_ray r, double t, t_object *ob, t_set *set);
double		ratio_sp(t_ray r, double t, t_object *ob, t_set *set);
double		ratio_pl(t_ray r, double t, t_object *ob, t_set *set);

#endif
