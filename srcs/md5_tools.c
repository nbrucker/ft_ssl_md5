/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:02:53 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/22 11:02:54 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "md5.h"
#include "libft.h"
#include "ft_ssl.h"

void		ft_fill_hash_md5(char *str, uint32_t x)
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
	ft_memdel((void**)&tmp);
}

t_md5		*ft_init_md5(void)
{
	t_md5	*md5;

	if (!(md5 = (t_md5*)malloc(sizeof(t_md5))))
		ft_error("Malloc error");
	md5->a0 = 0x67452301;
	md5->b0 = 0xefcdab89;
	md5->c0 = 0x98badcfe;
	md5->d0 = 0x10325476;
	return (md5);
}

void		ft_fill_hash_sha256(char *str, uint32_t x)
{
	char	*tmp;

	tmp = ft_itao_base(x, 4);
	ft_strcpy(str, tmp);
	ft_memdel((void**)&tmp);
}

t_sha256	*ft_init_sha256(void)
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
