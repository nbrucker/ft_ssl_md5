/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_option.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:54:20 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/21 16:54:20 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"

void	ft_handle_s_md5(int ac, char **av, t_env *env, int *i)
{
	t_hash	*hash;

	if (*i + 1 >= ac)
		ft_error("ft_ssl: Error: option requires an argument -- s");
	hash = ft_get_hash_env(av[*i + 1]);
	ft_call_hash(env, hash);
	ft_print_str_md5(hash->hash, hash->str, env);
	ft_memdel((void**)&hash->hash);
	ft_memdel((void**)&hash);
	*i += 1;
	env->got = 1;
}

void	ft_handle_p_md5(t_env *env)
{
	t_hash	*hash;
	t_read	*read;

	read = ft_read(0);
	hash = ft_get_hash_env(read->str);
	hash->len = read->len;
	ft_call_hash(env, hash);
	ft_putstr(hash->str);
	ft_putendl(hash->hash);
	ft_memdel((void**)&hash->hash);
	ft_memdel((void**)&hash->str);
	ft_memdel((void**)&hash);
	ft_memdel((void**)&read);
	env->got = 1;
}

void	ft_handle_file_md5(char **av, t_env *env, int i)
{
	t_hash	*hash;
	t_read	*read;
	int		fd;

	env->file = 1;
	if ((fd = open(av[i], O_RDONLY)) == -1)
	{
		ft_putstr("ft_ssl: ");
		ft_putstr(av[i]);
		ft_putendl(": No such file or directory");
		return ;
	}
	read = ft_read(fd);
	if (close(fd) == -1)
		ft_error("Error closing file");
	hash = ft_get_hash_env(read->str);
	hash->len = read->len;
	ft_call_hash(env, hash);
	ft_print_file_md5(hash->hash, av[i], env);
	ft_memdel((void**)&hash->hash);
	ft_memdel((void**)&hash->str);
	ft_memdel((void**)&hash);
	ft_memdel((void**)&read);
	env->got = 1;
}

void	ft_handle_no_arg_md5(t_env *env)
{
	t_hash	*hash;
	t_read	*read;

	read = ft_read(0);
	hash = ft_get_hash_env(read->str);
	hash->len = read->len;
	ft_call_hash(env, hash);
	ft_putendl(hash->hash);
	ft_memdel((void**)&hash->hash);
	ft_memdel((void**)&hash->str);
	ft_memdel((void**)&hash);
	ft_memdel((void**)&read);
	env->got = 1;
}

void	ft_handle_arguments_md5(int ac, char **av, t_env *env)
{
	int		i;

	i = 2;
	env->algo = av[1];
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-q") == 0 && env->file == 0)
			env->q = 1;
		else if (ft_strcmp(av[i], "-r") == 0 && env->file == 0)
			env->r = 1;
		else if (ft_strcmp(av[i], "-s") == 0 && env->file == 0)
			ft_handle_s_md5(ac, av, env, &i);
		else if (ft_strcmp(av[i], "-p") == 0 && env->file == 0)
			ft_handle_p_md5(env);
		else
			ft_handle_file_md5(av, env, i);
		i++;
	}
	if (env->got == 0)
		ft_handle_no_arg_md5(env);
}
