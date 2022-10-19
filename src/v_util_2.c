/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_util_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:15:32 by esukava           #+#    #+#             */
/*   Updated: 2022/05/29 15:29:08 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
**This function subtracts  t_fvector b from t_fvector a
*/
t_fvector	v_sub(t_fvector a, t_fvector b)
{
	t_fvector	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_fvector	v_div(t_fvector vector, float c)
{
	vector.x = vector.x / c;
	vector.y = vector.y / c;
	vector.z = vector.z / c;
	return (vector);
}

t_fvector	v_mult(t_fvector vector, float c)
{
	vector.x = vector.x * c;
	vector.y = vector.y * c;
	vector.z = vector.z * c;
	return (vector);
}
