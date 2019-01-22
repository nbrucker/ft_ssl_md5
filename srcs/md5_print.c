/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:58:05 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/21 16:58:05 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"

void	ft_print_file_md5(char *hash, char *name, t_env *env)
{
	if (env->q == 1)
		ft_putendl(hash);
	else if (env->r == 1)
	{
		ft_putstr(hash);
		ft_putchar(' ');
		ft_putendl(name);
	}
	else
	{
		ft_print_upper(env->algo);
		ft_putstr(" (");
		ft_putstr(name);
		ft_putstr(") = ");
		ft_putendl(hash);
	}
}

void	ft_print_str_md5(char *hash, char *str, t_env *env)
{
	if (env->q == 1)
		ft_putendl(hash);
	else if (env->r == 1)
	{
		ft_putstr(hash);
		ft_putstr(" \"");
		ft_putstr(str);
		ft_putendl("\"");
	}
	else
	{
		ft_print_upper(env->algo);
		ft_putstr(" (\"");
		ft_putstr(str);
		ft_putstr("\") = ");
		ft_putendl(hash);
	}
}
