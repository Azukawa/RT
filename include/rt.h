/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:58:49 by esukava           #+#    #+#             */
/*   Updated: 2022/10/13 20:46:22 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

//c lib
# include <unistd.h> //for write TBD
# include <fcntl.h>  //for O_RDONLY and open
# include <errno.h>  //for ERRNO
//SDL
# include "../libSDL2/include/SDL2/SDL.h"
//RTv1
# include "defines.h"
//libft
# include "libft.h"
# include "ft_gfx.h"

typedef struct s_object{
	t_fvector	pos;
	t_fvector	dir;
	float		r;
	int			type;
	float		angle;
	t_color		color;
	t_bool		mirror;
	int			tx_type;
}				t_object;

typedef struct s_ray{
	t_fvector	start;
	t_fvector	dir;
}				t_ray;

typedef struct s_cam{
	t_fvector	pos;
	t_fvector	dir;
	t_fvector	rot;
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

//superstruct that holds all the subsystem structs.
typedef struct s_rt {
	t_rend		rend;
	int			global_fps;
	t_cam		cam;
	t_bool		redraw;
	float		t;
	t_color		amb_col;
	t_ray		r_prm;
	t_ray		r_lght;
	float		uv_u;
	float		uv_v;
	t_object	*object;
	uint		objcount;
	t_object	light[10];
	t_color		colors[10];
	uint		col_switch;
	int			curobj;
	int			light_count;
	int			cur_light;
	float		t_scale;
	t_bool		mir_hit;
	t_color		mir_image;
	SDL_Surface	*surf;
}				t_rt;

void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);
void		keyevent(t_rt *rt, SDL_Event *e);

t_fvector	v_cross(t_fvector va, t_fvector vb);
float		v_dot(t_fvector va, t_fvector vb);
float		v_len(t_fvector v);
t_fvector	v_normalize(t_fvector v);
t_fvector	v_add(t_fvector a, t_fvector b);
t_fvector	v_sub(t_fvector a, t_fvector b);
t_fvector	v_div(t_fvector vector, float c);
t_fvector	v_mult(t_fvector vector, float c);

void		quadratic_equation(t_fvector abc, float *t0, float *t1);

t_bool		ray_plane_intersect(t_ray *r, t_object *p, float *t);
t_bool		ray_sphere_intersect(t_ray *r, t_object *s, float *t);
t_bool		ray_cyl_intersect(t_ray *r, t_object *obj, float *result);
t_bool		ray_cone_intersect(t_ray *r, t_object *cone, float *hit_distance);
void		ray_trough_screen(t_rt *rt, int x, int y);
t_bool		ray_object_intersect(t_ray *ray, t_object *obj, float *t);
t_bool		draw_light(t_rt *rt, float *t, int x, int y);
void		v_rot_x(t_fvector *vec, float rad);
void		v_rot_y(t_fvector *vec, float rad);
void		v_rot_z(t_fvector *vec, float rad);
t_fvector	v_rot_xyz(t_fvector vec, t_fvector rot);
void		draw_to_window(t_rt *rt);

t_fvector	find_object_normal(t_object *object, t_ray *ray);
void		raytracer(t_rt *rt, int x, int y);
t_bool		parse_c_dir(t_rt *rt, char *str);
t_bool		parse_c_pos(t_rt *rt, char *str);
uint32_t	convert_to(uint32_t c, uint *i);
int			create_bmp(char *filename, t_buffer *i);
//COLOR
t_color		uint_to_col(uint32_t color);
uint32_t	col_to_uint(t_color color);
t_color		col_lerp(t_color c1, t_color c2, float p);
t_color		col_blend(t_color base, t_color mix, float p);
t_color		col_multiply(t_color color, float m);
t_color		col_mult_colors(t_color a, t_color b);
t_color		col_add(t_color base, t_color mix, float p);
//texturing
void		uv_map(t_rt *rt, t_ray *ray);
t_color		apply_check(t_rt *rt, float scale, t_color oc);
t_color		apply_sqr_tex(t_rt *rt, float scale);
//parser
t_fvector	read_3dvec(char *line);
t_color		read_color(char *line);
void		read_cam(t_rt *rt, char *line);
void		read_objcount(t_rt *rt, char *line);
void		set_color(t_color *color, char *ptr);
void		set_scale(float *scale, char *ptr);
void		read_file(t_rt *rt, char *argv);
void		init_sphere(t_object *obj, t_fvector orig, float radius, t_color c);
void		init_plane(t_object *obj, t_fvector orig, t_fvector dir, t_color c);
void		init_cyl(t_object *obj, t_fvector orig, t_fvector dir, t_color c);
void		init_cone(t_object *obj, t_fvector orig, t_fvector dir, t_color c);

void		apply_3d_mods(t_object *obj, t_fvector r, t_fvector t);
t_mat4		mm_init_unitmatrix(void);
t_mat4		mm_init_translation(float x, float y, float z);
t_fvector	mm_multiply_vector(t_fvector v, t_mat4 m);
t_mat4		mm_multiply_matrix(t_mat4 ma, t_mat4 mb);

void		init_tex(t_object *object, char *line);
void		init_mirror(t_object *object, char *line);
void		init_light(t_rt *rt, char *line);
t_color		assign_color(t_rt *rt, t_ray lray, t_fvector n, t_color mix);
t_bool		in_shadow(t_rt *rt, t_ray light_ray, t_fvector dist);
void		update_scene(t_rt *rt);

#endif
