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

#include "md5.h"
#include "ft_ssl.h"
#include "libft.h"

uint32_t	g_s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

uint32_t	g_k[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
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

void	ft_inner_md5_algo(t_md5 *md5, uint32_t j)
{
	if (j < 16)
	{
		md5->f = (md5->b & md5->c) | ((~md5->b) & md5->d);
		md5->g = j;
	}
	else if (j < 32)
	{
		md5->f = (md5->d & md5->b) | ((~md5->d) & md5->c);
		md5->g = (5 * j + 1) % 16;
	}
	else if (j < 48)
	{
		md5->f = md5->b ^ md5->c ^ md5->d;
		md5->g = (3 * j + 5) % 16;
	}
	else
	{
		md5->f = md5->c ^ (md5->b | (~md5->d));
		md5->g = (7 * j) % 16;
	}
	md5->f = md5->f + md5->a + g_k[j] + md5->chunk[md5->g];
	md5->a = md5->d;
	md5->d = md5->c;
	md5->c = md5->b;
	md5->b = md5->b + ft_left_rotate(md5->f, g_s[j]);
}

void	ft_md5_algo(t_hash *hash, t_md5 *md5, char *new)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < hash->hash_len)
	{
		ft_copy_len((void*)md5->chunk, (void*)new + i, 64);
		md5->a = md5->a0;
		md5->b = md5->b0;
		md5->c = md5->c0;
		md5->d = md5->d0;
		j = 0;
		while (j < 64)
		{
			ft_inner_md5_algo(md5, j);
			j++;
		}
		md5->a0 += md5->a;
		md5->b0 += md5->b;
		md5->c0 += md5->c;
		md5->d0 += md5->d;
		i += 64;
	}
}

char	*ft_init_md5_hash(t_hash *hash)
{
	char	*new;

	hash->hash_len = (hash->len + 1) * 8;
	while (hash->hash_len % 512 != 448)
		hash->hash_len += 8;
	hash->hash_len = (hash->hash_len + 64) / 8;
	if (!(new = ft_strnew(hash->hash_len)))
		ft_error("Malloc error");
	ft_copy_len(new, hash->str, hash->len);
	new[hash->len] = (char)128;
	new[hash->hash_len - 1] = ((uint64_t)(hash->len * 8) &
		0xFF00000000000000) >> 56;
	new[hash->hash_len - 2] = ((uint64_t)(hash->len * 8) &
		0xFF000000000000) >> 48;
	new[hash->hash_len - 3] = ((uint64_t)(hash->len * 8) &
		0xFF0000000000) >> 40;
	new[hash->hash_len - 4] = ((uint64_t)(hash->len * 8) & 0xFF00000000) >> 32;
	new[hash->hash_len - 5] = ((uint64_t)(hash->len * 8) & 0xFF000000) >> 24;
	new[hash->hash_len - 6] = ((uint64_t)(hash->len * 8) & 0xFF0000) >> 16;
	new[hash->hash_len - 7] = ((uint64_t)(hash->len * 8) & 0xFF00) >> 8;
	new[hash->hash_len - 8] = (uint64_t)(hash->len * 8) & 0xFF;
	return (new);
}

void	ft_md5(t_hash *hash)
{
	char	*new;
	t_md5	*md5;

	new = ft_init_md5_hash(hash);
	md5 = ft_init_md5();
	ft_md5_algo(hash, md5, new);
	if (!(hash->hash = ft_strnew(33)))
		ft_error("Malloc error");
	ft_fill_hash_md5(hash->hash, md5->a0);
	ft_fill_hash_md5(hash->hash + 8, md5->b0);
	ft_fill_hash_md5(hash->hash + 16, md5->c0);
	ft_fill_hash_md5(hash->hash + 24, md5->d0);
	ft_memdel((void**)&new);
	ft_memdel((void**)&md5);
}
