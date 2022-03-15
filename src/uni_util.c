/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uni_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:15:12 by esukava           #+#    #+#             */
/*   Updated: 2022/02/23 13:03:40 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

float	lerp1d(float a, float b, float t)
{
	return ((1 - t) * a + t * b);
}

//this functions takes in values between 0 and 255
uint32_t	get_color2(unsigned char r, unsigned char g, unsigned char b)
{
	return ((255 << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

float	two_point_dist(t_fvector a, t_fvector b)
{
	float		ret;
	t_fvector	temp;

	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	temp.z = a.z - b.z;
	ret = sqrt((temp.x * temp.x) + (temp.y * temp.y) + (temp.z * temp.z));
	return (ret);
}

void	quadratic_equation(t_fvector abc, float *t0, float *t1)
{
	float	discriminant;
	float	denominator;

	discriminant = abc.y * abc.y - 4 * (abc.x * abc.z);
	denominator = 2 * abc.x;
	if (discriminant < 0 || denominator == 0 || fabsf(discriminant) < 0.001f)
	{
		*t0 = -1;
		*t1 = -1;
		return ;
	}
	*t0 = (-abc.y - sqrtf(discriminant)) / denominator;
	*t1 = (-abc.y + sqrtf(discriminant)) / denominator;
}
