#include "minirt.h"

void	check_color(t_vec color)
{
	if (color.x < 0 || color.x > 255)
		exit(printf("color error\n"));
	if (color.y < 0 || color.y > 255)
		exit(printf("color error\n"));
	if (color.z < 0 || color.z > 255)
		exit(printf("color error\n"));
}

void	check_viewpoint(t_vec view_point)
{
	if (view_point.x < -1 || view_point.x > 1)
		exit(printf("vector error\n"));
	if (view_point.y < -1 || view_point.y > 1)
		exit(printf("vector error\n"));
	if (view_point.z < -1 || view_point.z > 1)
		exit(printf("vector error\n"));
	if (length(view_point) == 0)
		exit(printf("vector error\n"));
}

void	set_camera(t_camera *camera, char *map)
{
	map++;
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	camera->location = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	camera->view_point = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	camera->fov = tan(degrees_to_radians(ft_atof(&map) / 2.0));
	if (camera->fov < 0 || camera->fov > 180)
		exit(printf("fov error\n"));
	check_viewpoint(camera->view_point);
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	if (map[0] != '\0')
		exit(printf("%c is wrong parameter\n", map[0]));
}

void	set_light(t_light *light, char *map)
{
	map++;
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	light->location = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	light->power = ft_atof(&map);
	if (light->power < 0 || light->power > 1)
		exit(printf("light power error\n"));
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	if (map[0] != '\0')
		exit(printf("%c is wrong parameter\n", map[0]));
}

t_sphere	*set_sphere(char *map)
{
	t_sphere	*sphere;

	map = map + 2;
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	sphere = malloc(sizeof(t_sphere) * 1);
	sphere->center = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	sphere->radius = ft_atof(&map);
	sphere->color = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	check_color(sphere->color);
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	if (map[0] != '\0')
		exit(printf("%c is wrong parameter\n", map[0]));
	return (sphere);
}

t_plane	*set_plane(char *map)
{
	t_plane *plane;

	map = map + 2;
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	plane = malloc(sizeof(t_plane) * 1);
	plane->center = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	plane->normal = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	plane->color = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	check_viewpoint(plane->normal);
	check_color(plane->color);
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	if (map[0] != '\0')
		exit(printf("%c is wrong parameter\n", map[0]));
	return (plane);
}

t_cylinder	*set_cylinder(char *map)
{
	t_cylinder *cy;

	map = map + 2;
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	cy = malloc(sizeof(t_cylinder) * 1);
	cy->center = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	cy->normal = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	cy->radius = ft_atof(&map);
	cy->height = ft_atof(&map);
	cy->color = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	check_viewpoint(cy->normal);
	cy->normal = unit_vector(cy->normal);
	check_color(cy->color);
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	if (map[0] != '\0')
		exit(printf("%c is wrong parameter\n", map[0]));
	
	return (cy);
}

void	set_am_light(t_am_light *am_light, char *map)
{
	map++;
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	am_light->am_light = ft_atof(&map);
	am_light->color = make_vec(ft_atof(&map), ft_atof(&map), ft_atof(&map));
	if (am_light->am_light < 0 || am_light->am_light > 1)
		exit(printf("light power error\n"));
	check_color(am_light->color);
	while (map[0] == ' ' || (map[0] >= 9 && map[0] <= 13))
		map++;
	if (map[0] != '\0')
		exit(printf("%c is wrong parameter\n", map[0]));
}