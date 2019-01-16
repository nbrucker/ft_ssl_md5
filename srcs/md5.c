/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:19:15 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/15 18:19:16 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"

uint32_t	s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
					5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
					4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
					6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

uint32_t	k[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
			0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
			0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
			0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
			0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
			0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
			0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
			0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
			0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
			0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
			0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
			0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
			0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
			0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
			0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
			0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

void		ft_fill_hash(char *str, uint32_t x)
{
	char	*tmp;
	int		i;

	tmp = ft_itao_base(x, 4);
	i = 0;
	while (i < 8)
	{
		str[i + 1] = tmp[7 - i];
		str[i] = tmp[6 - i];
		i += 2;
	}
	ft_strdel(&tmp);
}

char	*ft_md5(char *str)
{
	char		*hash;
	uint32_t	len;
	uint32_t	new_len;
	char		*new;
	uint32_t	i;
	uint32_t	j;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	a0 = 0x67452301;
	uint32_t	b0 = 0xefcdab89;
	uint32_t	c0 = 0x98badcfe;
	uint32_t	d0 = 0x10325476;
	uint32_t	f;
	uint32_t	g;
	uint32_t	chunk[16];

	len = ft_strlen(str);
	new_len = (len + 1) * 8;
	while (new_len % 512 != 448)
		new_len += 8;
	new_len = (new_len + 64) / 8;
	if (!(new = ft_strnew(new_len)))
		ft_error("Malloc error");
	ft_strcpy(new, str);
	new[len] = (char)128;
	new[new_len - 1] = ((uint64_t)(len * 8) & 0xFF00000000000000) >> 56;
	new[new_len - 2] = ((uint64_t)(len * 8) & 0xFF000000000000) >> 48;
	new[new_len - 3] = ((uint64_t)(len * 8) & 0xFF0000000000) >> 40;
	new[new_len - 4] = ((uint64_t)(len * 8) & 0xFF00000000) >> 32;
	new[new_len - 5] = ((uint64_t)(len * 8) & 0xFF000000) >> 24;
	new[new_len - 6] = ((uint64_t)(len * 8) & 0xFF0000) >> 16;
	new[new_len - 7] = ((uint64_t)(len * 8) & 0xFF00) >> 8;
	new[new_len - 8] = (uint64_t)(len * 8) & 0xFF;

	i = 0;
	while (i < new_len)
	{
		ft_copy_len((char*)chunk, new + i, 64);

		a = a0;
		b = b0;
		c = c0;
		d = d0;

		j = 0;
		while (j < 64)
		{
			if (j < 16)
			{
				f = (b & c) | ((~b) & d);
				g = j;
			}
			else if (j < 32)
			{
				f = (d & b) | ((~d) & c);
				g = (5 * j + 1) % 16;
			}
			else if (j < 48)
			{
				f = b ^ c ^ d;
				g = (3 * j + 5) % 16;
			}
			else
			{
				f = c ^ (b | (~d));
				g = (7 * j) % 16;
			}
			f = f + a + k[j] + chunk[g];
			a = d;
			d = c;
			c = b;
			b = b + ft_left_rotate(f, s[j]);
			j++;
		}
		a0 += a;
		b0 += b;
		c0 += c;
		d0 += d;
		i += 64;
	}
	if (!(hash = ft_strnew(33)))
		ft_error("Malloc error");
	ft_fill_hash(hash, a0);
	ft_fill_hash(hash + 8, b0);
	ft_fill_hash(hash + 16, c0);
	ft_fill_hash(hash + 24, d0);
	ft_strdel(&new);
	return (hash);
}
