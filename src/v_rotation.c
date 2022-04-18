/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_rotation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:25:28 by eniini            #+#    #+#             */
/*   Updated: 2022/04/18 18:14:00 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	rotate_x(float *z, float *y, float r)
{
	float	prev_y;

	prev_y = *y;
	*y = prev_y * cosf(r * DEG_TO_RAD) + *z * sin(r * DEG_TO_RAD);
	*z = -prev_y * sinf(r * DEG_TO_RAD) + *z * cos(r * DEG_TO_RAD);
}

static void	rotate_y(float *x, float *z, float r)
{
	float	prev_x;

	prev_x = *x;
	*x = prev_x * cosf(r * DEG_TO_RAD) + *z * sinf(r * DEG_TO_RAD);
	*z = -prev_x * sinf(r * DEG_TO_RAD) + *z * cosf(r * DEG_TO_RAD);
}

static void	rotate_z(float *x, float *y, float r)
{
	float	prev_x;
	float	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cosf(r * DEG_TO_RAD) - prev_y * sinf(r * DEG_TO_RAD);
	*y = prev_x * sinf(r * DEG_TO_RAD) + prev_y * cosf(r * DEG_TO_RAD);
}

/*
*	Rotate vector around the given vector.
*/
t_fvector	v_3d_p_rot(t_fvector rot_p, t_fvector pivot_p, t_fvector rot)
{
	t_fvector	angle;
	t_fvector	sub;

	angle.x = (int)rot.x % 360;
	angle.y = (int)rot.y % 360;
	angle.z = (int)rot.z % 360;
	sub = v_sub(rot_p, pivot_p);
	rotate_z(&sub.x, &sub.y, angle.z);
	rotate_y(&sub.x, &sub.z, angle.y);
	rotate_x(&sub.z, &sub.y, angle.x);
	return (v_add(sub, pivot_p));
}

/*
*	Rotate vector around its origin.
*/
t_fvector	v_3d_orig_rot(t_fvector point, t_fvector rot)
{
	t_fvector	angle;

	angle.x = (int)rot.x % 360;
	angle.y = (int)rot.y % 360;
	angle.z = (int)rot.z % 360;
	rotate_z(&point.x, &point.y, angle.z);
	rotate_y(&point.x, &point.z, angle.y);
	rotate_x(&point.z, &point.y, angle.x);
	return (point);
}
