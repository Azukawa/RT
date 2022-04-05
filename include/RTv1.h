/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:58:49 by esukava           #+#    #+#             */
/*   Updated: 2022/04/05 16:19:23 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

//c lib
# include <unistd.h> //for write TBD
# include <fcntl.h>  //for O_RDONLY and open
//SDL
# include "../libSDL2/include/SDL2/SDL.h"
//RTv1
# include "defines.h"

# define DEG_TO_RAD 0.01745329251
# define RAD_TO_DEG 57.2957795131

typedef int		t_bool;
# define TRUE	1
# define FALSE	0

enum e_type {
	SPHERE,
	PLANE,
	CYL,
	CONE,
	LIGHT
};

typedef struct s_color{
	float	red;
	float	green;
	float	blue;
}				t_color;

typedef struct s_object{
	t_fvector	pos;
	t_fvector	dir;
	int			material;
	float		r;
	int			type;
	float		angle;
	t_color		intensity;
}				t_object;

typedef struct s_plane{
	t_fvector	pos;
	t_fvector	dir;
	int			material;
}				t_plane;

typedef struct s_cylinder{
	t_fvector	pos;
	t_fvector	dir;
	float		r;
	int			material;
}				t_cylinder;

typedef struct s_cone{
	t_fvector	pos;
	t_fvector	dir;
	float		r;
	float		angle;
}				t_cone;

typedef struct s_ray{
	t_fvector	start;
	t_fvector	dir;
}				t_ray;

typedef struct s_material{
	t_color	diffuse;
	float	reflection;
}				t_material;

typedef struct s_sphere{
	t_fvector	pos;
	float		r;
	int			material;
}				t_sphere;

typedef struct s_light{
	t_color		intensity;
	t_fvector	pos;

}				t_light;

typedef struct s_cam{
	t_fvector	pos;
	t_fvector	dir;
	t_fvector	rot;
	float		aspect;
	float		fov;
	float		horz;
	float		vert;
	t_fvector	norm;
	t_fvector	front;
	t_fvector	right;
	t_fvector	up;
}				t_cam;

//Holds everything related directly to SDL's drawbuffer.
typedef struct s_rend
{
	SDL_Renderer	*renderer;
	SDL_Window		*win;
	SDL_Texture		*win_tex;
	void			*win_pixels;
	t_buffer		win_buffer;
	int				win_pixel_pitch;
	t_bool			run;
}					t_rend;

//Keyevent handling.
typedef struct s_keys {
	t_bool		up_pressed;
	t_bool		down_pressed;
	t_bool		left_pressed;
	t_bool		right_pressed;
	t_bool		fps_switch;
	t_bool		mouse_switch;
	t_bool		rot_switch;
	t_bool		is_grayscale;
}				t_keys;

//superstruct that holds all the subsystem structs.
typedef struct s_rt {
	t_rend		rend;
	t_keys		keys;
	int			global_fps;
	t_material	material[5];
	t_sphere	sphere[5];
	t_plane		plane[5];
	t_cylinder	cylinder[5];
	t_cone		cone[5];
	t_light		light[5];
	t_object	object[10];
	int			xvar;
	int			yvar;
	int			zvar;
	int			object_count;
	int			sx;
	int			sy;
	t_cam		cam;
	t_bool		run;
	char		scene[100][100];
	int			scene_len;
	float		t;
}				t_rt;

uint32_t	color_lerp(uint32_t c1, uint32_t c2, double p);
void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);
void		init_tests(t_rt *rt);
void		ales_rayc(t_rt *rt);
void		keyevent(t_rt *rt, SDL_Event *e);
t_fvector	v_cross(t_fvector va, t_fvector vb);
float		v_dot(t_fvector va, t_fvector vb);
float		v_len(t_fvector v);
t_fvector	v_normalize(t_fvector v);
t_fvector	v_add(t_fvector a, t_fvector b);
float		lerp1d(float a, float b, float t);
t_fvector	v_sub(t_fvector a, t_fvector b);
t_fvector	v_div(t_fvector vector, float c);
t_fvector	v_mult(t_fvector vector, float c);
uint32_t	get_color2(unsigned char r, unsigned char g, unsigned char b);
float		two_point_dist(t_fvector a, t_fvector b);
void		quadratic_equation(t_fvector abc, float *t0, float *t1);
float		ft_fmin(float a, float b);
float		ft_fmax(float a, float b);
t_bool		ray_plane_intersect(t_ray *r, t_object *p, float *t);
t_bool		ray_sphere_intersect(t_ray *r, t_object *s, float *t);
t_bool		ray_cyl_intersect(t_ray *r, t_object *obj, float *result);
t_bool		ray_cone_intersect(t_ray *r, t_object *obj, float *result);
t_ray		ray_trough_screen(t_rt *rt);
t_bool		ray_object_intersect(t_ray *ray, t_object *obj, float *t);
t_bool		draw_light(t_ray *ray, t_rt *rt, float *t);
void		v_rot_x(t_fvector *vec, float rad);
void		v_rot_y(t_fvector *vec, float rad);
void		v_rot_z(t_fvector *vec, float rad);
t_fvector	v_rot_xyz(t_fvector vec, t_fvector rot);
void		draw_to_window(t_rt *rt);
t_bool		parse(char *str, t_rt *rt);
t_bool		readscene(char *str, t_rt *rt);
t_bool		parse_light(t_rt *rt, char *str);
t_bool		saveline(char *ret, char *str);
t_bool		parse_angle(t_rt *rt, char *str, int index);
t_bool		parse_material(t_rt *rt, char *str, int index);
t_bool		parse_r(t_rt *rt, char *str, int index);
t_bool		parse_dir(t_rt *rt, char *str, int index);
t_bool		parse_pos(t_rt *rt, char *str, int index);
t_bool		str_to_int(int *i, char *str, float *pos);
t_bool		val_sym(char c, int i);
t_bool		parse_type(t_rt *rt, char *str, int index, int i);
t_bool		parse_quantity(t_rt *rt, char *str);
void		skip_white(int *i, char *str);
void		init_material(t_rt *rt);
void		init_light(t_rt *rt);
void		init_player(t_rt *rt);
void		init(t_rt *rt);
t_fvector	find_object_normal(t_object *object, t_ray *ray);
void		cone_normal(t_fvector new_start, t_object *object, t_fvector *n);
void		raytracer(t_rt *rt, int i);
t_bool		parse_c_dir(t_rt *rt, char *str);
t_bool		parse_c_pos(t_rt *rt, char *str);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			ft_clamp_i(int value, int min, int max);
void		ft_bzero(void *s, size_t n);
void		*ft_memalloc(size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);
size_t		ft_strlen(const char *s);
int			get_next_line(const int fd, char **line);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_strdel(char **as);
char		*ft_strndup(const char *s1, size_t n);
uint32_t	convert_to_grayscale(uint32_t c);
int			create_bmp(char *filename, t_buffer *i);
uint32_t	col_to_uint(t_color color);
t_color		col_lerp(t_color c1, t_color c2, float p);
t_color		col_blend(t_color base, t_color mix, float p);
t_color		col_multiply(t_color color, float m);

#endif
