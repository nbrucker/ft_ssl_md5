/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:19:30 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/15 18:19:30 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"
#include "ft_ssl.h"
#include "libft.h"

static uint32_t	g_k[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da,0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070,0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static void		ft_fill_hash(char *str, uint32_t x)
{
	char	*tmp;

	tmp = ft_itao_base(x, 4);
	ft_strcpy(str, tmp);
	ft_memdel((void**)&tmp);
}

t_sha256		*ft_init_sha256(void)
{
	t_sha256	*sha256;

	if (!(sha256 = (t_sha256*)malloc(sizeof(t_sha256))))
		ft_error("Malloc error");
	sha256->h0 = 0x6a09e667;
	sha256->h1 = 0xbb67ae85;
	sha256->h2 = 0x3c6ef372;
	sha256->h3 = 0xa54ff53a;
	sha256->h4 = 0x510e527f;
	sha256->h5 = 0x9b05688c;
	sha256->h6 = 0x1f83d9ab;
	sha256->h7 = 0x5be0cd19;
	return (sha256);
}

char	*ft_init_sha256_hash(t_hash *hash)
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
	new[hash->hash_len - 8] = ((uint64_t)(hash->len * 8) &
		0xFF00000000000000) >> 56;
	new[hash->hash_len - 7] = ((uint64_t)(hash->len * 8) &
		0xFF000000000000) >> 48;
	new[hash->hash_len - 6] = ((uint64_t)(hash->len * 8) &
		0xFF0000000000) >> 40;
	new[hash->hash_len - 5] = ((uint64_t)(hash->len * 8) & 0xFF00000000) >> 32;
	new[hash->hash_len - 4] = ((uint64_t)(hash->len * 8) & 0xFF000000) >> 24;
	new[hash->hash_len - 3] = ((uint64_t)(hash->len * 8) & 0xFF0000) >> 16;
	new[hash->hash_len - 2] = ((uint64_t)(hash->len * 8) & 0xFF00) >> 8;
	new[hash->hash_len - 1] = (uint64_t)(hash->len * 8) & 0xFF;
	return (new);
}

void		ft_a(t_sha256 *sha256)
{
	uint32_t	j;

	j = 0;
	while (j < 16)
	{
		sha256->tmp = sha256->chunk[j];
		sha256->chunk[j] = (sha256->tmp & 0xFF) << 24;
		sha256->chunk[j] += (sha256->tmp & 0xFF00) << 8;
		sha256->chunk[j] += (sha256->tmp & 0xFF0000) >> 8;
		sha256->chunk[j] += (sha256->tmp & 0xFF000000) >> 24;
		j++;
	}
	j = 16;
	while (j < 64)
	{
		sha256->s0 = ft_right_rotate(sha256->chunk[j - 15], 7) ^ ft_right_rotate(sha256->chunk[j - 15], 18) ^ (sha256->chunk[j - 15] >> 3);
		sha256->s1 = ft_right_rotate(sha256->chunk[j - 2], 17) ^ ft_right_rotate(sha256->chunk[j - 2], 19) ^ (sha256->chunk[j - 2] >> 10);
		sha256->chunk[j] = sha256->chunk[j - 16] + sha256->s0 + sha256->chunk[j - 7] + sha256->s1;
		j++;
	}
	sha256->a = sha256->h0;
	sha256->b = sha256->h1;
	sha256->c = sha256->h2;
}

void		ft_b(t_sha256 *sha256)
{
	uint32_t	j;

	j = 0;
	while (j < 64)
	{
		sha256->s1 = ft_right_rotate(sha256->e, 6) ^ ft_right_rotate(sha256->e, 11) ^ ft_right_rotate(sha256->e, 25);
		sha256->ch = (sha256->e & sha256->f) ^ ((~sha256->e) & sha256->g);
		sha256->tmp1 = sha256->h + sha256->s1 + sha256->ch + g_k[j] + sha256->chunk[j];
		sha256->s0 = ft_right_rotate(sha256->a, 2) ^ ft_right_rotate(sha256->a, 13) ^ ft_right_rotate(sha256->a, 22);
		sha256->maj = (sha256->a & sha256->b) ^ (sha256->a & sha256->c) ^ (sha256->b & sha256->c);
		sha256->tmp2 = sha256->s0 + sha256->maj;
		sha256->h = sha256->g;
		sha256->g = sha256->f;
		sha256->f = sha256->e;
		sha256->e = sha256->d + sha256->tmp1;
		sha256->d = sha256->c;
		sha256->c = sha256->b;
		sha256->b = sha256->a;
		sha256->a = sha256->tmp1 + sha256->tmp2;
		j++;
	}
}

void			ft_sha256(t_hash *hash)
{
	char		*new;
	t_sha256	*sha256;
	uint32_t	i;

	new = ft_init_sha256_hash(hash);
	sha256 = ft_init_sha256();

	i = 0;
	while (i < hash->hash_len)
	{
		ft_copy_len((void*)sha256->chunk, (void*)new + i, 64);
		ft_a(sha256);
		sha256->d = sha256->h3;
		sha256->e = sha256->h4;
		sha256->f = sha256->h5;
		sha256->g = sha256->h6;
		sha256->h = sha256->h7;
		ft_b(sha256);
		sha256->h0 += sha256->a;
		sha256->h1 += sha256->b;
		sha256->h2 += sha256->c;
		sha256->h3 += sha256->d;
		sha256->h4 += sha256->e;
		sha256->h5 += sha256->f;
		sha256->h6 += sha256->g;
		sha256->h7 += sha256->h;
		i += 64;
	}
	if (!(hash->hash = ft_strnew(65)))
		ft_error("Malloc error");
	ft_fill_hash(hash->hash, sha256->h0);
	ft_fill_hash(hash->hash + 8, sha256->h1);
	ft_fill_hash(hash->hash + 16, sha256->h2);
	ft_fill_hash(hash->hash + 24, sha256->h3);
	ft_fill_hash(hash->hash + 32, sha256->h4);
	ft_fill_hash(hash->hash + 40, sha256->h5);
	ft_fill_hash(hash->hash + 48, sha256->h6);
	ft_fill_hash(hash->hash + 56, sha256->h7);
	ft_memdel((void**)&new);
	ft_memdel((void**)&sha256);
}
