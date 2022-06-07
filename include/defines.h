/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:56:17 by esukava           #+#    #+#             */
/*   Updated: 2022/06/07 10:11:40 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

//WINDOW
# define WIN_W	800
# define WIN_H	600
# define WIN_HW 400
# define WIN_HH 300
# define WIN_NAME	"esukava/eniini interactive raytracer ver. 0.25"

# define ROUGHNESS		120.0f
# define RAY_LIMIT		20000.0f
# define RAY_DEPTH		3
# define REFRAC_FALLOFF	5.0f
# define AMBIENT_MIN	0.0f
# define AMBIENT_MAX	1.0f

# define DEG_TO_RAD 0.01745329251
# define RAD_TO_DEG 57.2957795131

enum e_type {
	SPHERE,
	PLANE,
	CYL,
	CONE
};

typedef int		t_bool;
# define TRUE	1
# define FALSE	0

typedef struct s_fvector {
	float	x;
	float	y;
	float	z;
	float	w;
}			t_fvector;

//4 x 4 matrix
typedef struct s_mat4 {
	float	m[4][4];
}			t_mat4;

typedef struct s_color {
	float	red;
	float	green;
	float	blue;
}				t_color;

//Datatype to store an ARBG image data. Each pixel can be found by calculating
//[(h * y) + (x % w)]
typedef struct s_buffer {
	uint32_t	*px;
	uint32_t	w;
	uint32_t	h;
}				t_buffer;

#endif