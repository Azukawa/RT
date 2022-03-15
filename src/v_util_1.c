/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_util_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:15:23 by esukava           #+#    #+#             */
/*   Updated: 2022/02/23 21:03:28 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_fvector	v_cross(t_fvector va, t_fvector vb)
{
	t_fvector	result;

	result.x = va.y * vb.z - va.z * vb.y;
	result.y = va.z * vb.x - va.x * vb.z;
	result.z = va.x * vb.y - va.y * vb.x;
	return (result);
}

float	v_dot(t_fvector va, t_fvector vb)
{
	return (va.x * vb.x + va.y * vb.y + va.z * vb.z);
}

float	v_len(t_fvector v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_fvector	v_normalize(t_fvector v)
{
	t_fvector	ret;
	float		l;

	l = v_len(v);
	ret.x = v.x / l;
	ret.y = v.y / l;
	ret.z = v.z / l;
	return (ret);
}

t_fvector	v_add(t_fvector a, t_fvector b)
{
	t_fvector	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}
