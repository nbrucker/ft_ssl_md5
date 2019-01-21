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
	if (ac < 2)
		ft_error("usage: ft_ssl command [command opts] [command args]");
	else if (ft_strcmp(av[1], "md5") != 0 && ft_strcmp(av[1], "sha256") != 0)
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
}

void	ft_call_hash(t_env *env, t_hash *hash)
{
	if (ft_strcmp(env->algo, "md5") == 0)
		ft_md5(hash);
	else if (ft_strcmp(env->algo, "sha256") == 0)
		ft_sha256(hash);
	else
		ft_error("Unexpected error");
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
	return (0);
}
