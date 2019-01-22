/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:18:49 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/15 18:18:50 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"

void	ft_print_upper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(ft_toupper(str[i]));
		i++;
	}
}

t_read	*ft_read(int fd)
{
	char	buf[4096 + 1];
	t_read	*elem;
	char	*tmp;
	int		ret;

	if (!(elem = (t_read*)malloc(sizeof(t_read))))
		ft_error("Malloc error");
	if (!(elem->str = ft_strnew(1)))
		ft_error("Malloc error");
	while ((ret = read(fd, buf, 4096)) > 0)
	{
		elem->len += ret;
		buf[ret] = 0;
		tmp = elem->str;
		if (!(elem->str = ft_strjoin(elem->str, buf)))
			ft_error("Malloc error");
		ft_memdel((void**)&tmp);
	}
	if (ret == -1)
		ft_error("Error reading input");
	return (elem);
}

void	ft_copy_len(void *dst, void *src, size_t len)
{
	size_t	i;
	char	*a;
	char	*b;

	a = (char*)dst;
	b = (char*)src;
	i = 0;
	while (i < len)
	{
		a[i] = b[i];
		i++;
	}
}

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (j > i)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

char	*ft_itao_base(int value, int size)
{
	unsigned long long	nbr;
	int					i;
	char				*str;
	char				*hex;

	if ((hex = ft_strdup("0123456789abcdef")) == NULL)
		ft_error("Malloc error");
	if ((str = ft_strnew((size * 2) + 1)) == NULL)
		ft_error("Malloc error");
	nbr = value;
	i = 0;
	while (nbr != 0 && i < size * 2)
	{
		str[i] = hex[nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	while (i < size * 2)
	{
		str[i] = '0';
		i++;
	}
	str[i] = 0;
	free(hex);
	return (ft_strrev(str));
}
