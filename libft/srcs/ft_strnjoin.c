/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t len1, size_t len2)
{
	char	*str;
	size_t	i;
	size_t	n;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = len1 + len2 + 1;
	if ((str = (char*)malloc(sizeof(char) * i)) == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	n = 0;
	while (n < len2)
	{
		str[i + n] = s2[n];
		n++;
	}
	str[i + n] = 0;
	return (str);
}
