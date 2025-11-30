/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skteifan <skteifan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:35:07 by skteifan          #+#    #+#             */
/*   Updated: 2025/11/26 21:35:07 by skteifan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	rgb_to_uint32(int rgb[3])
{
	return (((uint32_t)rgb[0] << 24)
		| ((uint32_t)rgb[1] << 16)
		| ((uint32_t)rgb[2] << 8)
		| 255);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_tex_pixel_color(mlx_texture_t *tex, int tex_x, int tex_y)
{
	uint8_t		*pixels;
	int			i;
	uint32_t	color;

	pixels = tex->pixels;
	i = (tex_y * tex->width + tex_x) * 4;
	color = get_rgba(pixels[i + 0], pixels[i + 1],
			pixels[i + 2], pixels[i + 3]);
	return (color);
}
