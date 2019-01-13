#include "ft_ssl.h"
#include "libft.h"

static uint32_t k[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
				0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
				0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
				0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
				0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
				0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
				0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
				0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static char	*ft_copyn(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

uint32_t	ft_right_rotate(uint32_t x, uint32_t c)
{
	return (x >> c) | (x << (32 - c));
}

static void	ft_test_print(char *str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		// printf("%d", str[i] & 0x80 ? 1 : 0);
		// printf("%d", str[i] & 0x40 ? 1 : 0);
		// printf("%d", str[i] & 0x20 ? 1 : 0);
		// printf("%d", str[i] & 0x10 ? 1 : 0);
		// printf("%d", str[i] & 0x08 ? 1 : 0);
		// printf("%d", str[i] & 0x04 ? 1 : 0);
		// printf("%d", str[i] & 0x02 ? 1 : 0);
		// printf("%d", str[i] & 0x01 ? 1 : 0);
		printf("%x ", str[i]);
		i++;
	}
}

char	*ft_sha256(char *str)
{
	char		*hash;
	uint32_t 	len;
	uint32_t	new_len;
	char		*new;
	uint32_t	chunk[64];
	uint32_t 	i;
	uint32_t 	j;
	uint32_t 	s0;
	uint32_t 	s1;
	uint32_t	h0 = 0x6a09e667;
	uint32_t	h1 = 0xbb67ae85;
	uint32_t	h2 = 0x3c6ef372;
	uint32_t	h3 = 0xa54ff53a;
	uint32_t	h4 = 0x510e527f;
	uint32_t	h5 = 0x9b05688c;
	uint32_t	h6 = 0x1f83d9ab;
	uint32_t	h7 = 0x5be0cd19;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;

	len = ft_strlen(str);
	new_len = (len + 1) * 8;
	while (new_len % 512 != 448)
		new_len += 8;
	new_len = (new_len + 64) / 8;
	if (!(new = ft_strnew(new_len)))
		ft_error("Malloc error");
	ft_strcpy(new, str);
	new[len] = 128;
	new[new_len - 8] = (uint64_t)(len * 8) & 0xFF00000000000000;
	new[new_len - 7] = (uint64_t)(len * 8) & 0xFF000000000000;
	new[new_len - 6] = (uint64_t)(len * 8) & 0xFF0000000000;
	new[new_len - 5] = (uint64_t)(len * 8) & 0xFF00000000;
	new[new_len - 4] = (uint64_t)(len * 8) & 0xFF000000;
	new[new_len - 3] = (uint64_t)(len * 8) & 0xFF0000;
	new[new_len - 2] = (uint64_t)(len * 8) & 0xFF00;
	new[new_len - 1] = (uint64_t)(len * 8) & 0xFF;
	ft_test_print(new, new_len);
	printf("\n%d\n", len * 8);

	i = 0;
	while (i < new_len)
	{
		ft_copyn((void*)chunk, new + i, 64);
		j = 0;
		while (j < 16)
		{
			uint32_t tmp = chunk[j];
			chunk[j] = (tmp & 0xFF) << 24;
			chunk[j] += (tmp & 0xFF00) << 8;
			chunk[j] += (tmp & 0xFF0000) >> 8;
			chunk[j] += (tmp & 0xFF000000) >> 24;
			j++;
		}
		j = 16;
		while (j < 64)
		{
			s0 = ft_right_rotate(chunk[j - 15], 7) ^ ft_right_rotate(chunk[j - 15], 18) ^ (chunk[j - 15] >> 3);
			s1 = ft_right_rotate(chunk[j - 2], 17) ^ ft_right_rotate(chunk[j - 2], 19) ^ (chunk[j - 2] >> 10);
			chunk[j] = chunk[j - 16] + s0 + chunk[j - 7] + s1;
			j++;
		}
		j = 0;
		while (j < 64)
		{
			printf("%-.8x ", chunk[j]);
			j++;
		}
		printf("\n");

		a = h0;
		b = h1;
		c = h2;
		d = h3;
		e = h4;
		f = h5;
		g = h6;
		h = h7;

		j = 0;
		while (j < 64)
		{
			s1 = ft_right_rotate(e, 6) ^ ft_right_rotate(e, 11) ^ ft_right_rotate(e, 25);
			uint32_t ch = (e & f) ^ ((~e) & g);
			uint32_t tmp1 = h + s1 + ch + k[j] + chunk[j];
			s0 = ft_right_rotate(a, 2) ^ ft_right_rotate(a, 13) ^ ft_right_rotate(a, 22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t tmp2 = s0 + maj;

			h = g;
			g = f;
			f = e;
			e = d + tmp1;
			d = c;
			c = b;
			b = a;
			a = tmp1 + tmp2;
			j++;
		}
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
		h4 += e;
		h5 += f;
		h6 += g;
		h7 += h;
		i += 64;
	}
	printf("%x %x %x %x %x %x %x %x\n", h0, h1, h2, h3, h4, h5, h6, h7);
	if (!(hash = ft_strnew(33)))
		ft_error("Malloc error");
	ft_strdel(&new);
	return (hash);
}