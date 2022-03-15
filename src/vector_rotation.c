/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:15:44 by esukava           #+#    #+#             */
/*   Updated: 2022/02/20 21:15:47 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	v_rot_x(t_fvector *vec, float rad)
{
	t_fvector	prev;

	prev.z = vec->z;
	prev.y = vec->y;
	vec->z = prev.z * cos(rad) - prev.y * sin(rad);
	vec->y = prev.z * sin(rad) + prev.y * cos(rad);
}

void	v_rot_y(t_fvector *vec, float rad)
{
	t_fvector	prev;

	prev.x = vec->x;
	prev.z = vec->z;
	vec->x = prev.x * cos(rad) - prev.z * sin(rad);
	vec->z = prev.x * sin(rad) + prev.z * cos(rad);
}

void	v_rot_z(t_fvector *vec, float rad)
{
	t_fvector	prev;

	prev.y = vec->y;
	prev.x = vec->x;
	vec->x = prev.x * cos(rad) - prev.y * sin(rad);
	vec->y = prev.x * sin(rad) + prev.y * cos(rad);
}

t_fvector	v_rot_xyz(t_fvector vec, t_fvector rot)
{
	t_fvector	ret;

	ret = vec;
	v_rot_x(&ret, DEG_TO_RAD * rot.x);
	v_rot_y(&ret, DEG_TO_RAD * rot.y);
	v_rot_z(&ret, DEG_TO_RAD * rot.z);
	return (ret);
}
