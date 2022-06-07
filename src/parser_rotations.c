/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:37:48 by eniini            #+#    #+#             */
/*   Updated: 2022/05/29 18:03:49 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_mat4	mm_init_rotationmatrix_x(float rad_angle)
{
	t_mat4	matrix;

	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = cosf(rad_angle);
	matrix.m[1][2] = sinf(rad_angle);
	matrix.m[2][1] = -sinf(rad_angle);
	matrix.m[2][2] = cosf(rad_angle);
	matrix.m[3][3] = 1.0f;
	return (matrix);
}

static t_mat4	mm_init_rotationmatrix_y(float rad_angle)
{
	t_mat4	matrix;

	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = cosf(rad_angle);
	matrix.m[0][2] = sinf(rad_angle);
	matrix.m[2][0] = -sinf(rad_angle);
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = cosf(rad_angle);
	matrix.m[3][3] = 1.0f;
	return (matrix);
}

static t_mat4	mm_init_rotationmatrix_z(float rad_angle)
{
	t_mat4	matrix;

	ft_bzero(&matrix, sizeof(t_mat4));
	matrix.m[0][0] = cosf(rad_angle);
	matrix.m[0][1] = sinf(rad_angle);
	matrix.m[1][0] = -sinf(rad_angle);
	matrix.m[1][1] = cosf(rad_angle);
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return (matrix);
}

/*
*	Apply rotation & translation values to the given [obj].
*	Rotation values given in angles.
*/
void	apply_3d_mods(t_object *obj, t_fvector r, t_fvector t)
{
	t_mat4	result;
	t_mat4	temp_1;
	t_mat4	temp_2;

	result = mm_init_unitmatrix();
	if (r.x || r.y || r.z)
	{
		temp_1 = mm_init_rotationmatrix_x(((int)r.x % 360) * DEG_TO_RAD);
		temp_2 = mm_init_rotationmatrix_y(((int)r.y % 360) * DEG_TO_RAD);
		result = mm_multiply_matrix(temp_1, temp_2);
		temp_1 = mm_init_rotationmatrix_z(((int)r.z % 360) * DEG_TO_RAD);
		result = mm_multiply_matrix(result, temp_1);
	}
	if (t.x || t.y || t.z)
		result = mm_multiply_matrix(result, mm_init_translation(t.x, t.y, t.z));
	obj->pos = mm_multiply_vector(obj->pos, result);
	obj->dir = mm_multiply_vector(obj->dir, result);
}
