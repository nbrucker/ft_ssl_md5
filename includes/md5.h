/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:23:39 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/21 16:23:40 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <stdlib.h>

typedef struct	s_md5
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	a0;
	uint32_t	b0;
	uint32_t	c0;
	uint32_t	d0;
	uint32_t	f;
	uint32_t	g;
	uint32_t	chunk[16];
}				t_md5;

#endif
