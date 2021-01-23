/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_endian.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:48:51 by loram             #+#    #+#             */
/*   Updated: 2021/01/14 02:48:52 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint64_t			swapendian_8_bytes(uint64_t num)
{
	num = (num & 0x00000000FFFFFFFF) << 32 | (num & 0xFFFFFFFF00000000) >> 32;
	num = (num & 0x0000FFFF0000FFFF) << 16 | (num & 0xFFFF0000FFFF0000) >> 16;
	num = (num & 0x00FF00FF00FF00FF) << 8 | (num & 0xFF00FF00FF00FF00) >> 8;
	return (num);
}

uint32_t			swapendian_4_bytes(uint32_t num)
{
	return (((num >> 24) & 0xFF) | ((num >> 8) & 0xFF00) |
			((num << 8) & 0xFF0000) | ((num << 24) & 0xFF000000));
}

uint16_t			swapendian_2_bytes(uint16_t num)
{
	return (((num >> 8) & 0xff) | ((num << 8) & 0xff00));
}

void				code_num_size_fd(u_int64_t num, int fd, size_t size)
{
	if (size == 2)
		num = swapendian_2_bytes((uint16_t)num);
	else if (size == 4)
		num = swapendian_4_bytes((uint32_t)num);
	else if (size == 8)
		num = swapendian_8_bytes(num);
	write(fd, &num, size);
}
