/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:19:10 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/15 18:19:10 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"

void	ft_handle_error(int ac, char **av)
{
	t_f	*ptr;
	t_f	*move;

	ptr = get_ptr();
	move = ptr;
	if (ac < 2)
		ft_error("usage: ft_ssl command [command opts] [command args]");
	while (move)
	{
		if (!ft_strcmp(av[1], move->str))
			break ;
		move = move->next;
	}
	if (!move)
	{
		ft_putstr("ft_ssl: Error: '");
		ft_putstr(av[1]);
		ft_putendl("' is an invalid command.");
		ft_putendl("\nStandart commands:");
		ft_putendl("\nMessage Digest commands:");
		ft_putendl("md5");
		ft_putendl("sha256");
		ft_error("\nCipher commands:");
	}
	free_ptr(ptr);
}

void	ft_call_hash(t_env *env, t_hash *hash)
{
	t_f	*ptr;
	t_f	*move;

	ptr = get_ptr();
	move = ptr;
	while (move)
	{
		if (!ft_strcmp(env->algo, move->str))
		{
			move->f(hash);
			break ;
		}
		move = move->next;
	}
	if (!move)
		ft_error("Unexpected error");
	free_ptr(ptr);
}

t_hash	*ft_get_hash_env(char *str)
{
	t_hash	*hash;

	if (!(hash = (t_hash*)malloc(sizeof(t_hash))))
		ft_error("Malloc error");
	hash->str = str;
	hash->hash = NULL;
	hash->len = strlen(hash->str);
	hash->hash_len = 0;
	return (hash);
}

t_env	*ft_get_env(void)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		ft_error("Malloc error");
	env->q = 0;
	env->r = 0;
	env->file = 0;
	env->got = 0;
	return (env);
}

int		main(int ac, char **av)
{
	t_env	*env;

	ft_handle_error(ac, av);
	env = ft_get_env();
	ft_handle_arguments_md5(ac, av, env);
	free(env);
	return (0);
}
